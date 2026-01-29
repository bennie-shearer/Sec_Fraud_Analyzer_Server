/**
 * SEC EDGAR Fraud Analyzer - Main Entry Point
 * Version: 2.1.2
 * Author: Bennie Shearer (Retired)
 * 
 * DISCLAIMER: This project is NOT funded, endorsed, or approved by the
 * U.S. Securities and Exchange Commission (SEC).
 * 
 * Cross-platform C++20 fraud detection server for SEC EDGAR filings.
 */

#include <sec_analyzer/version.h>
#include <sec_analyzer/types.h>
#include <sec_analyzer/logger.h>
#include <sec_analyzer/json.h>
#include <sec_analyzer/util.h>
#include <sec_analyzer/cache.h>
#include <sec_analyzer/http_server.h>
#include <sec_analyzer/sec_fetcher.h>
#include <sec_analyzer/analyzer.h>
#include <sec_analyzer/exporter.h>

#include <iostream>
#include <string>
#include <memory>
#include <csignal>
#include <atomic>
#include <fstream>

using namespace sec_analyzer;

// Global state
static std::atomic<bool> g_running{true};
static std::unique_ptr<HttpServer> g_server;

// Signal handler
void signal_handler(int signal) {
    LOG_INFO("Received signal {}, shutting down...", signal);
    g_running = false;
    if (g_server) {
        g_server->stop();
    }
}

// Print banner
void print_banner() {
    std::cout << "\n";
    std::cout << "+===============================================================+\n";
    std::cout << "|                SEC EDGAR Fraud Analyzer                       |\n";
    std::cout << "|                    Version " << SEC_ANALYZER_VERSION_STRING << "                              |\n";
    std::cout << "|                                                               |\n";
    std::cout << "|  Author: Bennie Shearer (Retired)                             |\n";
    std::cout << "+===============================================================+\n";
    std::cout << "\n";
}

// Print usage
void print_usage(const char* program) {
    std::cout << "Usage: " << program << " [options]\n\n";
    std::cout << "Options:\n";
    std::cout << "  --port <port>       Server port (default: 8080)\n";
    std::cout << "  --static <dir>      Static files directory (default: ./web)\n";
    std::cout << "  --cache <dir>       Cache directory (default: ./cache)\n";
    std::cout << "  --config <file>     Load configuration from JSON file\n";
    std::cout << "  --log-level <level> Set log level: debug, info, warning, error, critical\n";
    std::cout << "  --log-file <file>   Write logs to file (in addition to console)\n";
    std::cout << "  --verbose           Enable verbose logging (same as --log-level debug)\n";
    std::cout << "  --quiet             Suppress console output (errors only)\n";
    std::cout << "  --version           Show version information\n";
    std::cout << "  --help              Show this help message\n";
    std::cout << "\n";
    std::cout << "CLI Mode:\n";
    std::cout << "  --ticker <symbol>   Analyze company by ticker symbol\n";
    std::cout << "  --cik <number>      Analyze company by CIK number\n";
    std::cout << "  --years <count>     Number of years to analyze (default: 5)\n";
    std::cout << "  --format <type>     Output format: json, csv, html (default: json)\n";
    std::cout << "\n";
    std::cout << "Log Levels:\n";
    std::cout << "  debug    - Detailed debugging information\n";
    std::cout << "  info     - General operational messages (default)\n";
    std::cout << "  warning  - Warning messages\n";
    std::cout << "  error    - Error messages\n";
    std::cout << "  critical - Critical errors only\n";
    std::cout << "\n";
    std::cout << "Examples:\n";
    std::cout << "  " << program << " --port 8080 --static ./web\n";
    std::cout << "  " << program << " --port 8080 --log-level debug --log-file server.log\n";
    std::cout << "  " << program << " --ticker AAPL --years 3 --format json\n";
    std::cout << "  " << program << " --cik 0001024401 --format html > report.html\n";
    std::cout << "\n";
}

// Load configuration from file
bool load_config(ServerConfig& config, const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        LOG_ERROR("Failed to open config file: {}", path);
        return false;
    }
    
    std::string content((std::istreambuf_iterator<char>(file)),
                        std::istreambuf_iterator<char>());
    
    try {
        auto json = parse_json(content);
        
        if (json.contains("port")) {
            config.port = json.at("port").as_int();
        }
        if (json.contains("static_dir")) {
            config.static_dir = json.at("static_dir").as_string();
        }
        if (json.contains("cache_dir")) {
            config.cache_dir = json.at("cache_dir").as_string();
        }
        if (json.contains("user_agent")) {
            config.sec_user_agent = json.at("user_agent").as_string();
        }
        if (json.contains("cache_ttl")) {
            config.cache_ttl_seconds = json.at("cache_ttl").as_int();
        }
        if (json.contains("rate_limit")) {
            config.rate_limit_per_minute = json.at("rate_limit").as_int();
        }
        if (json.contains("verbose")) {
            config.verbose_logging = json.at("verbose").as_bool();
        }
        if (json.contains("log_level")) {
            config.log_level = json.at("log_level").as_string();
        }
        if (json.contains("log_file")) {
            config.log_file = json.at("log_file").as_string();
        }
        if (json.contains("cors")) {
            config.enable_cors = json.at("cors").as_bool();
        }
        
        // Load weights if present
        if (json.contains("weights")) {
            auto& w = json.at("weights");
            if (w.contains("beneish")) config.weights.beneish = w.at("beneish").as_number();
            if (w.contains("altman")) config.weights.altman = w.at("altman").as_number();
            if (w.contains("piotroski")) config.weights.piotroski = w.at("piotroski").as_number();
            if (w.contains("fraud_triangle")) config.weights.fraud_triangle = w.at("fraud_triangle").as_number();
            if (w.contains("benford")) config.weights.benford = w.at("benford").as_number();
            if (w.contains("red_flags")) config.weights.red_flags = w.at("red_flags").as_number();
            config.weights.normalize();
        }
        
        LOG_INFO("Loaded configuration from {}", path);
        return true;
        
    } catch (const std::exception& e) {
        LOG_ERROR("Failed to parse config file: {}", e.what());
        return false;
    }
}

// CLI mode analysis
int run_cli_analysis(const std::string& ticker, const std::string& cik, 
                     int years, const std::string& format) {
    LOG_INFO("Running CLI analysis...");
    
    auto fetcher = std::make_shared<SECFetcher>();
    FraudAnalyzer analyzer;
    analyzer.set_fetcher(fetcher);
    
    AnalysisResult result;
    
    if (!ticker.empty()) {
        LOG_INFO("Analyzing ticker: {}", ticker);
        result = analyzer.analyze_by_ticker(ticker, years);
    } else if (!cik.empty()) {
        LOG_INFO("Analyzing CIK: {}", cik);
        result = analyzer.analyze_by_cik(cik, years);
    } else {
        LOG_ERROR("No ticker or CIK specified");
        return 1;
    }
    
    if (analyzer.has_error()) {
        LOG_ERROR("Analysis failed: {}", analyzer.get_last_error());
        std::cerr << "Error: " << analyzer.get_last_error() << "\n";
        return 1;
    }
    
    // Output result in requested format
    std::string output;
    if (format == "csv") {
        output = ResultExporter::to_csv(result);
    } else if (format == "html") {
        output = ResultExporter::to_html(result);
    } else {
        output = ResultExporter::to_json(result, true);
    }
    
    std::cout << output << "\n";
    return 0;
}

// Setup API routes
void setup_routes(HttpServer& server, std::shared_ptr<SECFetcher> fetcher,
                  std::shared_ptr<FraudAnalyzer> analyzer,
                  std::shared_ptr<Cache<std::string>> cache) {
    
    // Health check endpoint
    server.get("/api/health", [cache](const HttpRequest& req) {
        std::string json = ResultExporter::health_json(
            SEC_ANALYZER_VERSION_STRING,
            static_cast<int>(cache->size())
        );
        return HttpResponse::ok(json);
    });
    
    // Company lookup by ticker
    server.get("/api/company", [fetcher](const HttpRequest& req) {
        std::string ticker = req.get_param("ticker");
        std::string cik = req.get_param("cik");
        
        if (ticker.empty() && cik.empty()) {
            return HttpResponse::bad_request("Missing ticker or cik parameter");
        }
        
        std::optional<CompanyInfo> company;
        if (!ticker.empty()) {
            company = fetcher->lookup_company_by_ticker(ticker);
        } else {
            company = fetcher->lookup_company_by_cik(cik);
        }
        
        if (!company) {
            return HttpResponse::not_found();
        }
        
        // Build JSON response
        JsonObject obj;
        obj["name"] = company->name;
        obj["ticker"] = company->ticker;
        obj["cik"] = company->cik;
        obj["sic"] = company->sic;
        
        return HttpResponse::ok(JsonValue(obj).dump());
    });
    
    // Main analysis endpoint
    server.get("/api/analyze", [analyzer, cache](const HttpRequest& req) {
        std::string ticker = req.get_param("ticker");
        std::string cik = req.get_param("cik");
        int years = 5;
        
        try {
            years = std::stoi(req.get_param("years", "5"));
        } catch (...) {}
        
        if (ticker.empty() && cik.empty()) {
            return HttpResponse::bad_request("Missing ticker or cik parameter");
        }
        
        // Check cache
        std::string cache_key = "analysis:" + (ticker.empty() ? cik : ticker) + ":" + std::to_string(years);
        auto cached = cache->get(cache_key);
        if (cached) {
            LOG_DEBUG("Cache hit for {}", cache_key);
            return HttpResponse::ok(*cached);
        }
        
        // Perform analysis
        AnalysisResult result;
        if (!ticker.empty()) {
            result = analyzer->analyze_by_ticker(ticker, years);
        } else {
            result = analyzer->analyze_by_cik(cik, years);
        }
        
        if (analyzer->has_error()) {
            return HttpResponse::error(500, analyzer->get_last_error());
        }
        
        std::string json = ResultExporter::to_json(result);
        cache->set(cache_key, json);
        
        return HttpResponse::ok(json);
    });
    
    // Filings list endpoint
    server.get("/api/filings", [fetcher](const HttpRequest& req) {
        std::string ticker = req.get_param("ticker");
        std::string cik = req.get_param("cik");
        int years = 5;
        
        try {
            years = std::stoi(req.get_param("years", "5"));
        } catch (...) {}
        
        if (ticker.empty() && cik.empty()) {
            return HttpResponse::bad_request("Missing ticker or cik parameter");
        }
        
        std::string target_cik = cik;
        if (!ticker.empty()) {
            auto company = fetcher->lookup_company_by_ticker(ticker);
            if (!company) {
                return HttpResponse::not_found();
            }
            target_cik = company->cik;
        }
        
        auto filings = fetcher->get_filings(target_cik, years);
        
        JsonArray arr;
        for (const auto& f : filings) {
            JsonObject obj;
            obj["accession"] = f.accession_number;
            obj["form_type"] = f.form_type;
            obj["filed_date"] = f.filed_date;
            obj["fiscal_year"] = static_cast<double>(f.fiscal_year);
            arr.push_back(obj);
        }
        
        JsonObject result;
        result["filings"] = arr;
        result["count"] = static_cast<double>(filings.size());
        
        return HttpResponse::ok(JsonValue(result).dump());
    });
    
    // CIK search endpoint
    server.get("/api/cik/search", [fetcher](const HttpRequest& req) {
        std::string query = req.get_param("q");
        if (query.empty()) {
            return HttpResponse::bad_request("Missing q parameter");
        }
        
        auto companies = fetcher->search_companies(query);
        
        JsonArray arr;
        for (const auto& c : companies) {
            JsonObject obj;
            obj["name"] = c.name;
            obj["ticker"] = c.ticker;
            obj["cik"] = c.cik;
            arr.push_back(obj);
        }
        
        JsonObject result;
        result["results"] = arr;
        
        return HttpResponse::ok(JsonValue(result).dump());
    });
    
    // Cache management
    server.post("/api/cache/clear", [cache](const HttpRequest& req) {
        cache->clear();
        return HttpResponse::ok("{\"status\":\"cleared\"}");
    });
    
    // Export endpoints
    server.get("/api/export/csv", [analyzer](const HttpRequest& req) {
        // Similar to analyze but returns CSV
        std::string ticker = req.get_param("ticker");
        if (ticker.empty()) {
            return HttpResponse::bad_request("Missing ticker parameter");
        }
        
        auto result = analyzer->analyze_by_ticker(ticker, 5);
        std::string csv = ResultExporter::to_csv(result);
        
        HttpResponse res = HttpResponse::ok(csv, "text/csv");
        res.headers["Content-Disposition"] = "attachment; filename=\"analysis.csv\"";
        return res;
    });
    
    server.get("/api/export/html", [analyzer](const HttpRequest& req) {
        std::string ticker = req.get_param("ticker");
        if (ticker.empty()) {
            return HttpResponse::bad_request("Missing ticker parameter");
        }
        
        auto result = analyzer->analyze_by_ticker(ticker, 5);
        std::string html = ResultExporter::to_html(result);
        
        return HttpResponse::ok(html, "text/html");
    });
}

// Main entry point
int main(int argc, char* argv[]) {
    print_banner();
    
    // Default configuration
    ServerConfig config;
    config.port = 8080;
    config.static_dir = "./web";
    config.cache_dir = "./cache";
    config.sec_user_agent = "SECFraudAnalyzer/" SEC_ANALYZER_VERSION_STRING " educational@example.com";
    
    // CLI mode variables
    std::string cli_ticker;
    std::string cli_cik;
    int cli_years = 5;
    std::string cli_format = "json";
    bool cli_mode = false;
    
    // Parse command line arguments
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        
        if (arg == "--help" || arg == "-h") {
            print_usage(argv[0]);
            return 0;
        }
        if (arg == "--version" || arg == "-v") {
            std::cout << get_version_info() << "\n";
            return 0;
        }
        if (arg == "--port" && i + 1 < argc) {
            config.port = std::stoi(argv[++i]);
        }
        else if (arg == "--static" && i + 1 < argc) {
            config.static_dir = argv[++i];
        }
        else if (arg == "--cache" && i + 1 < argc) {
            config.cache_dir = argv[++i];
        }
        else if (arg == "--config" && i + 1 < argc) {
            if (!load_config(config, argv[++i])) {
                return 1;
            }
        }
        else if (arg == "--verbose") {
            config.verbose_logging = true;
            config.log_level = "debug";
        }
        else if (arg == "--quiet") {
            config.log_level = "error";
        }
        else if (arg == "--log-level" && i + 1 < argc) {
            config.log_level = argv[++i];
        }
        else if (arg == "--log-file" && i + 1 < argc) {
            config.log_file = argv[++i];
        }
        else if (arg == "--ticker" && i + 1 < argc) {
            cli_ticker = argv[++i];
            cli_mode = true;
        }
        else if (arg == "--cik" && i + 1 < argc) {
            cli_cik = argv[++i];
            cli_mode = true;
        }
        else if (arg == "--years" && i + 1 < argc) {
            cli_years = std::stoi(argv[++i]);
        }
        else if (arg == "--format" && i + 1 < argc) {
            cli_format = argv[++i];
        }
    }
    
    // CLI mode
    if (cli_mode) {
        // Apply logging settings for CLI mode
        Logger::instance().set_level_from_string(config.log_level);
        if (!config.log_file.empty()) {
            Logger::instance().set_file(config.log_file);
        }
        return run_cli_analysis(cli_ticker, cli_cik, cli_years, cli_format);
    }
    
    // Apply logging configuration
    Logger::instance().set_level_from_string(config.log_level);
    if (!config.log_file.empty()) {
        Logger::instance().set_file(config.log_file);
        LOG_INFO("Logging to file: {}", config.log_file);
    }
    
    // Server mode
    LOG_INFO("Starting SEC EDGAR Fraud Analyzer v{}", SEC_ANALYZER_VERSION_STRING);
    LOG_INFO("Log level: {}", config.log_level);
    LOG_INFO("Static directory: {}", config.static_dir);
    LOG_INFO("Cache directory: {}", config.cache_dir);
    
    // Setup signal handlers
    std::signal(SIGINT, signal_handler);
    std::signal(SIGTERM, signal_handler);
    
    // Create shared components
    auto cache = std::make_shared<Cache<std::string>>(config.cache_ttl_seconds);
    auto fetcher = std::make_shared<SECFetcher>(config.sec_user_agent);
    auto analyzer = std::make_shared<FraudAnalyzer>(config.weights);
    analyzer->set_fetcher(fetcher);
    
    // Create and configure server
    g_server = std::make_unique<HttpServer>();
    g_server->set_port(config.port);
    g_server->set_static_dir(config.static_dir);
    g_server->set_cors_enabled(config.enable_cors);
    
    // Setup API routes
    setup_routes(*g_server, fetcher, analyzer, cache);
    
    // Start server
    if (!g_server->start()) {
        LOG_CRITICAL("Failed to start server on port {}", config.port);
        return 1;
    }
    
    LOG_INFO("Server running on http://localhost:{}", config.port);
    LOG_INFO("Press Ctrl+C to stop");
    
    // Wait for shutdown
    while (g_running && g_server->is_running()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    
    LOG_INFO("Server stopped");
    return 0;
}
