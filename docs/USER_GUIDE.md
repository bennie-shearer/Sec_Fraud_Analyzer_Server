# SEC EDGAR Fraud Analyzer - User Guide

**Version:** 2.1.2  
**Author:** Bennie Shearer (Retired)

**DISCLAIMER: This project is NOT funded, endorsed, or approved by the U.S. Securities and Exchange Commission (SEC).**

---

## Table of Contents

1. [Getting Started](#1-getting-started)
2. [Web Interface](#2-web-interface)
3. [Analyzing Companies](#3-analyzing-companies)
4. [Understanding Results](#4-understanding-results)
5. [Command Line Options](#5-command-line-options)
6. [Tips](#6-tips)
7. [Limitations](#7-limitations)
8. [FAQ](#8-faq)

---

## 1. Getting Started

### Start Server

```bash
./sec_fraud_analyzer --port 8080
```

### Access Web Interface

Open `http://localhost:8080` or `web/index.html` in a browser.

---

## 2. Web Interface

### Toolbar

| Icon | Function | Shortcut |
|------|----------|----------|
| Download | Export JSON | Ctrl+S |
| Print | Print report | Ctrl+P |
| Moon | Dark mode | Ctrl+D |
| Code | Demo mode | Ctrl+M |

### Search Panel

- **Stock Ticker**: Enter ticker (AAPL, MSFT, BRK.A)
- **Analysis Scope**: Select years (1-10)
- **Filing Types**: 10-K, 10-Q, Amendments

---

## 3. Analyzing Companies

### Ticker Formats

| Input | Result |
|-------|--------|
| AAPL | Works |
| aapl | Works (case-insensitive) |
| BRK.A | Works (converts to BRK-A) |

### Batch Analysis

1. Click batch icon
2. Enter tickers (one per line)
3. Click "Analyze All"

---

## 4. Understanding Results

### Risk Levels

| Level | Score | Meaning |
|-------|-------|---------|
| LOW | 0-25 | Minimal concerns |
| MODERATE | 26-50 | Investigate further |
| HIGH | 51-75 | Significant flags |
| CRITICAL | 76-100 | Strong indicators |

### Model Scores

**Beneish M-Score:**
- M > -1.78: Likely manipulation
- M < -2.22: Unlikely

**Altman Z-Score:**
- Z > 2.99: Safe
- Z < 1.81: Distress

**Piotroski F-Score:**
- 8-9: Strong
- 0-4: Weak

---

## 5. Command Line Options

```bash
./sec_fraud_analyzer [options]

--port <number>     Server port (default: 8080)
--log-level <level> debug, info, warning, error
--log-file <path>   Log file path
--quiet             Suppress console output
```

---

## 6. Tips

1. Use 5 years for good trend visibility
2. Include all filing types
3. Compare peer companies
4. Check trends, not just single points
5. No single model is definitive

---

## 7. Limitations

1. **Data Availability**: Analysis depends on SEC EDGAR data availability
2. **XBRL Coverage**: Not all filings have complete XBRL data
3. **Industry Variations**: Model thresholds may vary by industry
4. **Historical Data**: Older filings may lack standardized data

---

## 8. FAQ

**Q: Is this legal?**  
A: Yes, all data is public from SEC EDGAR.

**Q: Why company not found?**  
A: May be delisted, private, or different ticker format.

**Q: Why revenues $0?**  
A: Some companies use different XBRL concepts.

**Q: Why slow?**  
A: SEC rate limits to 10/second. Cache speeds repeat queries.

---

**Version:** 2.1.2 | **Date:** January 2026
