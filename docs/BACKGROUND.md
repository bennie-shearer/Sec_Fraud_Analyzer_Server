# SEC EDGAR Fraud Analyzer - Background Document

**Version:** 2.1.2  
**Author:** Bennie Shearer (Retired)  
**Date:** January 2026

**DISCLAIMER: This project is NOT funded, endorsed, or approved by the U.S. Securities and Exchange Commission (SEC).**

---

## Table of Contents

1. [Introduction](#1-introduction)
2. [History of Financial Fraud Detection Systems](#2-history-of-financial-fraud-detection-systems)
   - 2.1 [Early Fraud Detection (Pre-1990s)](#21-early-fraud-detection-pre-1990s)
   - 2.2 [Statistical Revolution (1990s-2000s)](#22-statistical-revolution-1990s-2000s)
   - 2.3 [Modern Quantitative Era (2000s-Present)](#23-modern-quantitative-era-2000s-present)
   - 2.4 [Regulatory Response and Technology](#24-regulatory-response-and-technology)
3. [Purpose of Financial Fraud Detection Systems](#3-purpose-of-financial-fraud-detection-systems)
   - 3.1 [Protecting Investors](#31-protecting-investors)
   - 3.2 [Market Integrity](#32-market-integrity)
   - 3.3 [Regulatory Compliance](#33-regulatory-compliance)
   - 3.4 [Corporate Governance](#34-corporate-governance)
4. [The Broader Ecosystem](#4-the-broader-ecosystem)
   - 4.1 [SEC EDGAR System](#41-sec-edgar-system)
   - 4.2 [XBRL Financial Reporting](#42-xbrl-financial-reporting)
   - 4.3 [Commercial Fraud Detection Solutions](#43-commercial-fraud-detection-solutions)
   - 4.4 [Academic Research](#44-academic-research)
5. [How This Project Fits](#5-how-this-project-fits)
   - 5.1 [Educational Purpose](#51-educational-purpose)
   - 5.2 [Open Source Alternative](#52-open-source-alternative)
   - 5.3 [Cross-Platform Accessibility](#53-cross-platform-accessibility)
   - 5.4 [Zero External Dependencies](#54-zero-external-dependencies)
6. [Design Philosophy](#6-design-philosophy)
   - 6.1 [Multi-Model Approach](#61-multi-model-approach)
   - 6.2 [Transparency and Explainability](#62-transparency-and-explainability)
   - 6.3 [Real-Time Data Integration](#63-real-time-data-integration)
   - 6.4 [Conservative Risk Assessment](#64-conservative-risk-assessment)
   - 6.5 [Modern C++ Standards](#65-modern-c-standards)
7. [Fraud Detection Models Implemented](#7-fraud-detection-models-implemented)
   - 7.1 [Beneish M-Score](#71-beneish-m-score)
   - 7.2 [Altman Z-Score](#72-altman-z-score)
   - 7.3 [Piotroski F-Score](#73-piotroski-f-score)
   - 7.4 [Fraud Triangle Analysis](#74-fraud-triangle-analysis)
   - 7.5 [Benford's Law Analysis](#75-benfords-law-analysis)
8. [Architecture Overview](#8-architecture-overview)
   - 8.1 [Server Component](#81-server-component)
   - 8.2 [Web Client Component](#82-web-client-component)
   - 8.3 [Data Flow](#83-data-flow)
9. [Limitations and Disclaimers](#9-limitations-and-disclaimers)
10. [References](#10-references)

---

## 1. Introduction

The SEC EDGAR Fraud Analyzer is an educational and research tool designed to analyze publicly traded companies for potential financial statement fraud indicators. By combining multiple academically-validated fraud detection models with real-time SEC EDGAR data, this system provides a comprehensive view of financial health and fraud risk.

This document provides background on financial fraud detection systems, explains how this project fits into the broader ecosystem, and outlines the design philosophy that guided its development.

---

## 2. History of Financial Fraud Detection Systems

### 2.1 Early Fraud Detection (Pre-1990s)

Financial fraud detection has existed as long as financial markets themselves. Early methods relied primarily on:

- **Manual Auditing**: Accountants and auditors manually reviewed financial statements for inconsistencies
- **Ratio Analysis**: Basic financial ratios were compared against industry benchmarks
- **Red Flag Checklists**: Auditors used experience-based checklists to identify suspicious patterns
- **Whistleblower Reports**: Many frauds were detected through tips from employees or competitors

Notable early frauds that shaped detection practices:

| Year | Company | Amount | Impact |
|------|---------|--------|--------|
| 1938 | McKesson & Robbins | $19M | Led to mandatory independent audits |
| 1973 | Equity Funding Corp | $2B | Highlighted need for computer auditing |
| 1982 | ZZZZ Best | $100M | Exposed audit procedure weaknesses |

### 2.2 Statistical Revolution (1990s-2000s)

The 1990s saw the emergence of quantitative fraud detection models:

**1994 - Beneish M-Score**
Professor Messod Beneish of Indiana University developed the M-Score model, using eight financial variables to calculate the probability of earnings manipulation. This model successfully identified Enron as a potential manipulator before its collapse.

**1968/1983 - Altman Z-Score**
While originally developed by Edward Altman in 1968 for bankruptcy prediction, the Z-Score became widely used in the 1990s as a fraud indicator, as companies approaching financial distress often resort to fraudulent reporting.

**2000 - Piotroski F-Score**
Joseph Piotroski developed the F-Score at the University of Chicago to identify financially strong companies, but it also serves as a fraud detection tool by highlighting companies with deteriorating fundamentals.

### 2.3 Modern Quantitative Era (2000s-Present)

Major corporate scandals drove innovation in fraud detection:

| Year | Company | Fraud Amount | Key Issue |
|------|---------|--------------|-----------|
| 2001 | Enron | $74B loss | Off-balance-sheet entities |
| 2002 | WorldCom | $11B | Capitalized operating expenses |
| 2002 | Tyco | $600M | Executive theft |
| 2003 | HealthSouth | $2.7B | Inflated earnings |
| 2008 | Lehman Brothers | $50B | Hidden leverage |

These scandals resulted in:
- Sarbanes-Oxley Act (2002) mandating internal controls
- PCAOB (Public Company Accounting Oversight Board) creation
- Enhanced SEC enforcement capabilities
- Growth of forensic accounting as a profession
- Development of automated fraud detection systems

### 2.4 Regulatory Response and Technology

Modern fraud detection benefits from:

- **XBRL Reporting**: Standardized financial data since 2009
- **SEC EDGAR System**: Electronic filing and public access
- **Machine Learning**: Pattern recognition in large datasets
- **Real-Time Monitoring**: Continuous analysis of filings
- **Big Data Analytics**: Cross-referencing multiple data sources

---

## 3. Purpose of Financial Fraud Detection Systems

### 3.1 Protecting Investors

The primary purpose of fraud detection is investor protection:

- **Retirement Savings**: Pension funds and 401(k) plans invest in public companies
- **Individual Investors**: Retail investors rely on accurate financial statements
- **Institutional Investors**: Mutual funds and hedge funds need reliable data
- **Market Confidence**: Trust in financial reporting supports market participation

The SEC estimates that financial statement fraud costs investors $50-100 billion annually.

### 3.2 Market Integrity

Fraud detection supports fair and efficient markets:

- **Price Discovery**: Accurate information enables proper stock valuation
- **Capital Allocation**: Investment flows to legitimate, productive companies
- **Economic Growth**: Efficient capital markets support business expansion
- **International Competitiveness**: Trusted markets attract global investment

### 3.3 Regulatory Compliance

Fraud detection assists regulatory bodies:

- **SEC Enforcement**: Identifies companies requiring investigation
- **Audit Planning**: Helps auditors focus on high-risk areas
- **Risk-Based Supervision**: Prioritizes regulatory resources
- **Deterrence**: Visible detection systems discourage fraud attempts

### 3.4 Corporate Governance

Internal fraud detection supports good governance:

- **Board Oversight**: Audit committees use detection tools
- **Management Accountability**: CFOs and CEOs certify statements
- **Internal Audit**: Continuous monitoring of financial controls
- **Ethics Culture**: Detection systems reinforce ethical behavior

---

## 4. The Broader Ecosystem

### 4.1 SEC EDGAR System

The Electronic Data Gathering, Analysis, and Retrieval (EDGAR) system is the foundation of financial transparency:

**History:**
- 1984: EDGAR pilot program begins
- 1996: Electronic filing becomes mandatory
- 2009: XBRL tagging required for large companies
- 2020: Inline XBRL required for all filers

**Key Statistics:**
- Over 21 million filings available
- 3,000+ filing types
- 10+ terabytes of data
- Free public access

**Filing Types Relevant to Fraud Detection:**

| Form | Description | Frequency |
|------|-------------|-----------|
| 10-K | Annual report with audited financials | Annual |
| 10-Q | Quarterly report with unaudited financials | Quarterly |
| 8-K | Material event disclosures | Event-driven |
| DEF 14A | Proxy with executive compensation | Annual |

### 4.2 XBRL Financial Reporting

eXtensible Business Reporting Language (XBRL) revolutionized financial data:

**Benefits:**
- Standardized financial concepts across companies
- Machine-readable data elements
- Automatic data extraction
- Cross-company comparisons
- Historical trend analysis

**US-GAAP Taxonomy:**
- Over 15,000 standardized financial concepts
- Hierarchical structure for financial statements
- Annual updates to reflect accounting changes
- Extensions for company-specific items

### 4.3 Commercial Fraud Detection Solutions

The market includes several commercial offerings:

| Solution | Focus Area | Typical Cost |
|----------|------------|--------------|
| Audit Analytics | Restatements, auditor changes | $10,000+/year |
| Kensho/S&P Global | AI-powered analysis | Enterprise pricing |
| SAS Fraud Framework | Statistical detection | $50,000+/year |
| IDEA/ACL | Computer-assisted audit | $5,000+/year |

### 4.4 Academic Research

Ongoing research continues to advance the field:

**Key Research Areas:**
- Machine learning applications in fraud detection
- Natural language processing of management discussion
- Network analysis of corporate relationships
- Real-time anomaly detection algorithms
- Behavioral analysis of management

**Notable Researchers:**
- Messod Beneish (Indiana University) - M-Score
- Patricia Dechow (UC Berkeley) - Earnings quality
- Joseph Piotroski (Stanford) - F-Score
- Mark Nigrini (West Virginia) - Benford's Law applications

---

## 5. How This Project Fits

### 5.1 Educational Purpose

This project serves as an educational tool for:

- **Students**: Learning fraud detection concepts and implementation
- **Researchers**: Testing and validating models with real data
- **Practitioners**: Understanding detection methodologies
- **Investors**: Performing due diligence on investments

### 5.2 Open Source Alternative

Unlike commercial solutions, this project offers:

- **Free Access**: No licensing fees or subscriptions
- **Source Code**: Full transparency in calculations
- **Customization**: Modify algorithms as needed
- **Community**: Potential for collaborative improvement
- **Learning**: Understand exactly how detection works

### 5.3 Cross-Platform Accessibility

Designed for broad accessibility:

| Platform | Compiler | HTTP Client | Status |
|----------|----------|-------------|--------|
| Windows 10/11 | MSVC 2022 | WinHTTP | Verified |
| Windows 10/11 | MinGW-w64 | WinHTTP | Verified |
| Ubuntu 22.04+ | GCC 11+ | System curl | Verified |
| macOS 12+ | Clang 14+ | System curl | Verified |

### 5.4 Zero External Dependencies

Philosophy of minimal dependencies:

- **No External Libraries**: All functionality built-in
- **No Database Required**: File-based caching
- **No Framework Lock-in**: Portable C++20 code
- **Simple Deployment**: Single executable plus web files

---

## 6. Design Philosophy

### 6.1 Multi-Model Approach

Financial fraud is complex and multifaceted. No single model captures all indicators. This system combines five complementary models:

| Model | Focus Area | Default Weight |
|-------|------------|----------------|
| Beneish M-Score | Earnings manipulation | 30% |
| Altman Z-Score | Financial distress | 25% |
| Piotroski F-Score | Financial strength | 15% |
| Fraud Triangle | Behavioral factors | 15% |
| Benford's Law | Digit distribution | 5% |
| Red Flags | Qualitative indicators | 10% |

### 6.2 Transparency and Explainability

Unlike "black box" machine learning systems, this analyzer provides:

- **Component Scores**: Each model's contribution is visible
- **Calculation Details**: Full breakdown of each metric
- **Threshold Explanations**: Why a score triggers an alert
- **Historical Context**: Comparison with prior periods
- **Source Data**: Links to original SEC filings

### 6.3 Real-Time Data Integration

The system fetches live data from SEC EDGAR:

- **Current Filings**: Analyzes most recent 10-K and 10-Q
- **Historical Comparison**: Trends over multiple periods
- **Automatic Updates**: No manual data entry required
- **Rate Limiting**: Respects SEC API guidelines (10 req/sec)
- **Caching**: Reduces redundant API calls

### 6.4 Conservative Risk Assessment

The system errs on the side of caution:

- **False Positives Preferred**: Better to investigate than miss fraud
- **Weighted Thresholds**: Multiple indicators needed for high risk
- **Uncertainty Handling**: Missing data increases risk score
- **Clear Disclaimers**: Not a substitute for professional analysis

### 6.5 Modern C++ Standards

Technical design principles:

- **C++20 Features**: Modern language features where beneficial
- **Memory Safety**: Smart pointers and RAII throughout
- **Thread Safety**: Concurrent request handling
- **Platform Abstraction**: Clean separation of OS-specific code
- **No External Dependencies**: Standard library only

---

## 7. Fraud Detection Models Implemented

### 7.1 Beneish M-Score

**Purpose**: Detect earnings manipulation

**Formula**:
```
M = -4.84 + 0.92*DSRI + 0.528*GMI + 0.404*AQI + 0.892*SGI
    + 0.115*DEPI - 0.172*SGAI + 4.679*TATA - 0.327*LVGI
```

**Variables**:

| Variable | Name | Calculation |
|----------|------|-------------|
| DSRI | Days Sales Receivables Index | (Receivables/Sales)t / (Receivables/Sales)t-1 |
| GMI | Gross Margin Index | Gross Margint-1 / Gross Margint |
| AQI | Asset Quality Index | Asset Quality change |
| SGI | Sales Growth Index | Salest / Salest-1 |
| DEPI | Depreciation Index | Depreciation rate change |
| SGAI | SG&A Index | SG&A expense ratio change |
| TATA | Total Accruals to Assets | Accruals / Total Assets |
| LVGI | Leverage Index | Leverage ratio change |

**Interpretation**:
- M > -1.78: High probability of manipulation
- M < -2.22: Low probability of manipulation

### 7.2 Altman Z-Score

**Purpose**: Predict financial distress (often precedes fraud)

**Formula**:
```
Z = 1.2*A + 1.4*B + 3.3*C + 0.6*D + 1.0*E
```

**Variables**:

| Variable | Calculation |
|----------|-------------|
| A | Working Capital / Total Assets |
| B | Retained Earnings / Total Assets |
| C | EBIT / Total Assets |
| D | Market Value Equity / Total Liabilities |
| E | Sales / Total Assets |

**Interpretation**:
- Z > 2.99: Safe zone
- Z 1.81-2.99: Grey zone
- Z < 1.81: Distress zone

### 7.3 Piotroski F-Score

**Purpose**: Assess financial strength

**Scoring**: 0-9 points based on nine criteria

| # | Criterion | Points |
|---|-----------|--------|
| 1 | Positive net income | 0 or 1 |
| 2 | Positive operating cash flow | 0 or 1 |
| 3 | Increasing ROA | 0 or 1 |
| 4 | Cash flow > Net income | 0 or 1 |
| 5 | Decreasing long-term debt ratio | 0 or 1 |
| 6 | Increasing current ratio | 0 or 1 |
| 7 | No new shares issued | 0 or 1 |
| 8 | Increasing gross margin | 0 or 1 |
| 9 | Increasing asset turnover | 0 or 1 |

**Interpretation**:
- 8-9: Strong financial health
- 4-7: Average
- 0-3: Weak (fraud risk indicator)

### 7.4 Fraud Triangle Analysis

**Purpose**: Assess behavioral fraud indicators

**Components**:

**Pressure (Incentive):**
- Executive compensation tied to stock price
- Debt covenants near violation
- Analyst expectations to meet
- Cash flow problems

**Opportunity:**
- Weak internal controls
- Complex transactions
- Related party dealings
- Management override capability

**Rationalization:**
- Aggressive accounting policies
- History of restatements
- Auditor disagreements
- Tone at the top issues

### 7.5 Benford's Law Analysis

**Purpose**: Detect artificial number generation

**Principle**: In naturally occurring datasets, leading digits follow a specific distribution:

| Digit | Expected Frequency |
|-------|-------------------|
| 1 | 30.1% |
| 2 | 17.6% |
| 3 | 12.5% |
| 4 | 9.7% |
| 5 | 7.9% |
| 6 | 6.7% |
| 7 | 5.8% |
| 8 | 5.1% |
| 9 | 4.6% |

**Application**: Financial statement numbers should follow this distribution. Significant deviation suggests fabrication.

---

## 8. Architecture Overview

### 8.1 Server Component

**Technology**: C++20

**Responsibilities**:
- SEC EDGAR API communication
- XBRL data parsing
- Fraud model calculations
- Result aggregation
- HTTP API serving
- Response caching

### 8.2 Web Client Component

**Technology**: HTML5, CSS3, JavaScript (ES6+)

**Features**:
- Responsive design
- Dark mode support
- Interactive results display
- Export functionality (JSON, CSV, HTML)
- Configurable logging

### 8.3 Data Flow

```
User Input (Ticker: AAPL)
         |
         v
Web Client (JavaScript)
         |
         v
HTTP Request to Server
         |
         v
C++ Server receives request
         |
         v
Normalize ticker (BRK.A -> BRK-A)
         |
         v
Check cache for existing results
         |
    [Cache Hit]        [Cache Miss]
         |                   |
         v                   v
  Return cached       Fetch from SEC EDGAR
         |                   |
         +-------+-----------+
                 |
                 v
         Run Fraud Models
                 |
                 v
         Return JSON Response
                 |
                 v
         Display in Web UI
```

---

## 9. Limitations and Disclaimers

**This tool is for educational and research purposes only.**

**IMPORTANT: This project is NOT funded, endorsed, or approved by the U.S. Securities and Exchange Commission (SEC).**

**Data Limitations**:
1. **Data Availability**: Analysis depends on SEC EDGAR data availability
2. **XBRL Coverage**: Not all filings have complete XBRL data
3. **Industry Variations**: Model thresholds may vary by industry
4. **Historical Data**: Older filings may lack standardized data

**Model Limitations**:
1. Not a substitute for professional financial analysis
2. Cannot detect all types of fraud
3. False positives and negatives are possible
4. Historical models may not capture new fraud schemes
5. Data quality depends on SEC EDGAR accuracy
6. Not suitable for real-time trading decisions
7. Limited to US publicly traded companies

**Disclaimers**:
1. No warranty of accuracy or completeness
2. Not financial, legal, or investment advice
3. Users should consult qualified professionals
4. Past detection does not guarantee future detection
5. Results should be one input among many in decision-making
6. The authors assume no liability for investment decisions

---

## 10. References

### Academic Papers

1. Beneish, M.D. (1999). "The Detection of Earnings Manipulation." Financial Analysts Journal, 55(5), 24-36.

2. Altman, E.I. (1968). "Financial Ratios, Discriminant Analysis and the Prediction of Corporate Bankruptcy." Journal of Finance, 23(4), 589-609.

3. Piotroski, J.D. (2000). "Value Investing: The Use of Historical Financial Statement Information to Separate Winners from Losers." Journal of Accounting Research, 38, 1-41.

4. Cressey, D.R. (1953). Other People's Money: A Study in the Social Psychology of Embezzlement. Free Press.

5. Nigrini, M.J. (2012). Benford's Law: Applications for Forensic Accounting, Auditing, and Fraud Detection. Wiley.

### Regulatory Sources

- SEC EDGAR System: https://www.sec.gov/edgar
- SEC API Documentation: https://www.sec.gov/developer
- XBRL US: https://xbrl.us
- PCAOB: https://pcaobus.org

---

## Acknowledgments

- **Walter Hamscher** - Mentor and XBRL expert
- **SEC EDGAR** - Financial data source
- **Academic researchers** - Beneish, Altman, Piotroski, Cressey, Benford
- **CLion** by JetBrains s.r.o.
- **Claude** by Anthropic PBC

---

**Document Information**

| Field | Value |
|-------|-------|
| Document | BACKGROUND.md |
| Version | 2.1.2 |
| Author | Bennie Shearer (Retired) |
| Date | January 2026 |
| License | MIT |

---

*This document is part of the SEC EDGAR Fraud Analyzer project.*
*For educational and research purposes only.*
