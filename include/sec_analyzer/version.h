/**
 * SEC EDGAR Fraud Analyzer - Version Information
 * Version: 2.1.2
 * Author: Bennie Shearer (Retired)
 * 
 * DISCLAIMER: This project is NOT funded, endorsed, or approved by the
 * U.S. Securities and Exchange Commission (SEC).
 * 
 * Cross-platform C++20 implementation for Windows, Linux, and macOS.
 */

#ifndef SEC_ANALYZER_VERSION_H
#define SEC_ANALYZER_VERSION_H

#define SEC_ANALYZER_VERSION_MAJOR 2
#define SEC_ANALYZER_VERSION_MINOR 1
#define SEC_ANALYZER_VERSION_PATCH 2
#define SEC_ANALYZER_VERSION_STRING "2.1.2"

#define SEC_ANALYZER_COPYRIGHT "Copyright (c) 2026 Bennie Shearer"
#define SEC_ANALYZER_LICENSE "MIT License"
#define SEC_ANALYZER_DISCLAIMER "NOT funded, endorsed, or approved by the U.S. SEC"

namespace sec_analyzer {

/**
 * Get version string
 */
inline const char* get_version() {
    return SEC_ANALYZER_VERSION_STRING;
}

/**
 * Get full version information
 */
inline const char* get_version_info() {
    return "SEC EDGAR Fraud Analyzer v" SEC_ANALYZER_VERSION_STRING "\n"
           "Author: Bennie Shearer (Retired)\n"
           SEC_ANALYZER_COPYRIGHT "\n"
           SEC_ANALYZER_LICENSE "\n"
           SEC_ANALYZER_DISCLAIMER;
}

} // namespace sec_analyzer

#endif // SEC_ANALYZER_VERSION_H
