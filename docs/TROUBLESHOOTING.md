# SEC EDGAR Fraud Analyzer - Troubleshooting Guide

**Version:** 2.1.2  
**Author:** Bennie Shearer (Retired)

**DISCLAIMER: This project is NOT funded, endorsed, or approved by the U.S. Securities and Exchange Commission (SEC).**

---

## Table of Contents

1. [Build Issues](#build-issues)
2. [Runtime Issues](#runtime-issues)
3. [Web Client Issues](#web-client-issues)
4. [SEC API Issues](#sec-api-issues)
5. [Data Issues](#data-issues)

---

## Build Issues

### Error: "concept is a reserved keyword"

**Cause:** C++20 reserves `concept` as a keyword.

**Solution:** Update to v2.1.2+ where this is fixed. The parameter was renamed to `concept_name`.

---

### Error: "undefined reference to WinHttpOpen"

**Cause:** Missing WinHTTP library link on Windows.

**Solution:** Ensure `-lwinhttp` is in your link command:
```cmd
g++ ... -lws2_32 -lwinhttp
```

---

### Error: "curl: command not found" (Linux/macOS)

**Cause:** curl not installed on system.

**Solution:**
```bash
# Ubuntu/Debian
sudo apt install curl

# Fedora
sudo dnf install curl

# macOS (usually pre-installed)
brew install curl
```

---

### Error: CMake version too old

**Cause:** CMake 3.16+ required.

**Solution:**
```bash
# Ubuntu
sudo apt install cmake

# Or download from cmake.org
```

---

### Error: C++20 features not available

**Cause:** Compiler too old.

**Solution:** Update compiler:
- GCC 11+ required
- Clang 14+ required
- MSVC 2022 required

---

## Runtime Issues

### Server won't start: "Address already in use"

**Cause:** Port 8080 already in use by another process.

**Solution:**
```bash
# Use different port
./sec_fraud_analyzer --port 3000

# Or find and kill process using port 8080
# Linux/macOS:
lsof -i :8080
kill <PID>

# Windows:
netstat -ano | findstr :8080
taskkill /PID <PID> /F
```

---

### Server starts but no response

**Cause:** Firewall blocking connections.

**Solution:**
1. Check firewall settings
2. Ensure localhost access allowed
3. Try accessing http://127.0.0.1:8080 instead of localhost

---

### High memory usage

**Cause:** Large cache accumulation.

**Solution:**
1. Restart server to clear cache
2. Use `--cache-ttl` to reduce cache lifetime
3. Analyze fewer years of data

---

## Web Client Issues

### "Failed to connect to server"

**Causes and Solutions:**

1. **Server not running:**
   - Start the server first
   - Check server console for errors

2. **Wrong URL in config.json:**
   - Verify `apiUrl` matches server address
   - Default: `http://localhost:8080`

3. **CORS issues (if using different origin):**
   - Run web client from same origin as server
   - Or use the built-in server file serving

---

### Dark mode not working

**Cause:** CSS not loaded or cached.

**Solution:**
1. Hard refresh: Ctrl+Shift+R (Windows/Linux) or Cmd+Shift+R (macOS)
2. Clear browser cache
3. Verify style.css is present

---

### Export not working

**Cause:** Browser blocking downloads.

**Solution:**
1. Check browser download settings
2. Allow downloads from localhost
3. Try different browser

---

## SEC API Issues

### HTTP 403 Forbidden

**Cause:** SEC requires User-Agent with contact email.

**Solution:** Fixed in v1.7.11+. Update to latest version.

The User-Agent should be: `SECFraudAnalyzer/2.1.2 (contact@example.com)`

---

### HTTP 429 Too Many Requests

**Cause:** Exceeded SEC rate limit (10 requests/second).

**Solution:**
1. Wait a few minutes before retrying
2. Reduce batch size
3. Increase delay between requests

---

### "Company not found"

**Causes:**

1. **Wrong ticker format:**
   - Use SEC format: BRK-A not BRK.A
   - v1.7.14+ auto-converts periods to hyphens

2. **Delisted company:**
   - Use CIK lookup instead
   - Tools > CIK Lookup

3. **Private company:**
   - Only public SEC filers are searchable

---

### Slow response times

**Causes and Solutions:**

1. **First request (cache miss):**
   - Initial requests fetch from SEC
   - Subsequent requests use cache

2. **SEC servers busy:**
   - Try off-peak hours
   - Evenings and weekends usually faster

3. **Large data requests:**
   - Reduce years analyzed
   - Analyze fewer filing types

---

## Data Issues

### Revenue/Income showing $0

**Causes:**

1. **8-K filings:** Don't contain financial statements
   - Only 10-K and 10-Q have revenue/income

2. **Different XBRL concepts:**
   - Some companies use non-standard concepts
   - System tries multiple alternatives

3. **Missing XBRL data:**
   - Older filings may lack XBRL
   - Very recent filings may not be indexed yet

---

### Inconsistent scores across runs

**Cause:** SEC data updates or different fiscal periods selected.

**Solution:**
1. Use specific date ranges
2. Note that SEC may update historical data
3. Compare same filing types

---

### Missing filings

**Causes:**

1. **Too short time range:**
   - Increase years analyzed

2. **Filing type filtered out:**
   - Enable all filing types

3. **SEC indexing delay:**
   - New filings may take 24-48 hours to appear

---

## Getting Help

If issues persist:

1. Check server logs with `--log-level debug`
2. Check browser console (F12) for JavaScript errors
3. Verify SEC EDGAR is accessible: https://www.sec.gov/cgi-bin/browse-edgar

---

**Version:** 2.1.2 | **Date:** January 2026
