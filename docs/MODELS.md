# SEC EDGAR Fraud Analyzer - Fraud Detection Models

**Version:** 2.1.2  
**Author:** Bennie Shearer (Retired)

**DISCLAIMER: This project is NOT funded, endorsed, or approved by the U.S. Securities and Exchange Commission (SEC).**

---

## Table of Contents

1. [Overview](#1-overview)
2. [Beneish M-Score](#2-beneish-m-score)
3. [Altman Z-Score](#3-altman-z-score)
4. [Piotroski F-Score](#4-piotroski-f-score)
5. [Benford's Law Analysis](#5-benfords-law-analysis)
6. [Fraud Triangle Assessment](#6-fraud-triangle-assessment)
7. [Combined Risk Score](#7-combined-risk-score)
8. [Limitations](#8-limitations)

---

## 1. Overview

This application implements five academically-validated fraud detection models. Each model examines different aspects of financial health and manipulation risk.

| Model | Focus | Original Author | Year |
|-------|-------|-----------------|------|
| Beneish M-Score | Earnings manipulation | Messod Beneish | 1999 |
| Altman Z-Score | Bankruptcy risk | Edward Altman | 1968 |
| Piotroski F-Score | Financial strength | Joseph Piotroski | 2000 |
| Benford's Law | Number patterns | Frank Benford | 1938 |
| Fraud Triangle | Behavioral factors | Donald Cressey | 1953 |

---

## 2. Beneish M-Score

### Purpose

Detect earnings manipulation by analyzing financial statement ratios.

### Formula

```
M = -4.84 + 0.92*DSRI + 0.528*GMI + 0.404*AQI + 0.892*SGI
    + 0.115*DEPI - 0.172*SGAI + 4.679*TATA - 0.327*LVGI
```

### Variables

| Variable | Name | Formula | Interpretation |
|----------|------|---------|----------------|
| DSRI | Days Sales Receivables Index | (Receivables_t/Sales_t) / (Receivables_t-1/Sales_t-1) | >1.0 suggests revenue inflation |
| GMI | Gross Margin Index | GrossMargin_t-1 / GrossMargin_t | >1.0 suggests margin deterioration |
| AQI | Asset Quality Index | [1-(CA_t+PPE_t)/TA_t] / [1-(CA_t-1+PPE_t-1)/TA_t-1] | >1.0 suggests asset quality decline |
| SGI | Sales Growth Index | Sales_t / Sales_t-1 | High growth increases manipulation risk |
| DEPI | Depreciation Index | DepRate_t-1 / DepRate_t | >1.0 suggests slower depreciation |
| SGAI | SG&A Index | (SGA_t/Sales_t) / (SGA_t-1/Sales_t-1) | >1.0 suggests cost pressure |
| TATA | Total Accruals to Assets | (Income - CFO) / TotalAssets | High accruals suggest manipulation |
| LVGI | Leverage Index | Leverage_t / Leverage_t-1 | >1.0 suggests increasing debt |

### Interpretation

| M-Score | Risk Level | Meaning |
|---------|------------|---------|
| > -1.78 | HIGH | Likely manipulator (76% accuracy) |
| -1.78 to -2.22 | MODERATE | Borderline |
| < -2.22 | LOW | Unlikely manipulator |

### Historical Performance

- Successfully flagged Enron before collapse
- Successfully flagged WorldCom before collapse
- 76% accuracy in academic studies

---

## 3. Altman Z-Score

### Purpose

Predict bankruptcy risk. Financial distress often precedes or accompanies fraud.

### Formula

```
Z = 1.2*A + 1.4*B + 3.3*C + 0.6*D + 1.0*E
```

### Variables

| Variable | Formula | Weight | Measures |
|----------|---------|--------|----------|
| A | Working Capital / Total Assets | 1.2 | Liquidity |
| B | Retained Earnings / Total Assets | 1.4 | Cumulative profitability |
| C | EBIT / Total Assets | 3.3 | Operating efficiency |
| D | Market Value Equity / Total Liabilities | 0.6 | Solvency |
| E | Sales / Total Assets | 1.0 | Asset utilization |

### Interpretation

| Z-Score | Zone | Probability of Bankruptcy |
|---------|------|---------------------------|
| > 2.99 | Safe | Very low |
| 1.81 - 2.99 | Grey | Uncertain |
| < 1.81 | Distress | High |

### Variations

- **Original (1968):** For manufacturing companies
- **Z'-Score:** For private companies (removes market value)
- **Z''-Score:** For non-manufacturing/emerging markets

This implementation uses the original formula.

---

## 4. Piotroski F-Score

### Purpose

Evaluate financial strength through nine binary criteria.

### Scoring (0-9 points)

#### Profitability (0-4 points)

| # | Criterion | Condition for 1 Point |
|---|-----------|----------------------|
| 1 | ROA | Net Income > 0 |
| 2 | CFO | Operating Cash Flow > 0 |
| 3 | Delta ROA | ROA_t > ROA_t-1 |
| 4 | Accruals | CFO > Net Income |

#### Leverage/Liquidity (0-3 points)

| # | Criterion | Condition for 1 Point |
|---|-----------|----------------------|
| 5 | Delta Leverage | LTDebt/Assets_t < LTDebt/Assets_t-1 |
| 6 | Delta Liquidity | CurrentRatio_t > CurrentRatio_t-1 |
| 7 | Equity Offering | No new shares issued |

#### Operating Efficiency (0-2 points)

| # | Criterion | Condition for 1 Point |
|---|-----------|----------------------|
| 8 | Delta Margin | GrossMargin_t > GrossMargin_t-1 |
| 9 | Delta Turnover | AssetTurnover_t > AssetTurnover_t-1 |

### Interpretation

| F-Score | Rating | Meaning |
|---------|--------|---------|
| 8-9 | Strong | Excellent financial health |
| 5-7 | Moderate | Average financial health |
| 0-4 | Weak | Poor financial health, fraud risk |

---

## 5. Benford's Law Analysis

### Purpose

Detect artificially generated numbers by analyzing digit distribution.

### Principle

In naturally occurring datasets, leading digits follow a predictable distribution:

| Digit | Expected % | Formula |
|-------|------------|---------|
| 1 | 30.1% | log10(1 + 1/d) |
| 2 | 17.6% | log10(1 + 1/d) |
| 3 | 12.5% | log10(1 + 1/d) |
| 4 | 9.7% | log10(1 + 1/d) |
| 5 | 7.9% | log10(1 + 1/d) |
| 6 | 6.7% | log10(1 + 1/d) |
| 7 | 5.8% | log10(1 + 1/d) |
| 8 | 5.1% | log10(1 + 1/d) |
| 9 | 4.6% | log10(1 + 1/d) |

### Statistical Test

Chi-square test compares observed vs. expected frequencies:

```
X^2 = Sum[(Observed - Expected)^2 / Expected]
```

### Interpretation

| Deviation | Risk Level | Meaning |
|-----------|------------|---------|
| < 10% | LOW | Normal distribution |
| 10-20% | MODERATE | Monitor for anomalies |
| > 20% | HIGH | Possible fabrication |

### Limitations

- Requires sufficient data points (50+ recommended)
- Some legitimate datasets don't follow Benford's Law
- Best used with other indicators

---

## 6. Fraud Triangle Assessment

### Purpose

Evaluate behavioral and circumstantial factors conducive to fraud.

### Components

#### Pressure (Incentive) - Weight: 35%

| Factor | Indicator |
|--------|-----------|
| Financial targets | Executive compensation tied to stock |
| Debt covenants | Near covenant violation |
| Analyst expectations | Consistent "just meeting" estimates |
| Cash flow issues | Operating cash flow negative |
| Competition | Market share declining |

#### Opportunity - Weight: 40%

| Factor | Indicator |
|--------|-----------|
| Internal controls | Audit opinion qualified |
| Complexity | Unusual transactions |
| Related parties | Significant related-party dealings |
| Management override | CEO/CFO concentration |
| Audit committee | Weak oversight |

#### Rationalization - Weight: 25%

| Factor | Indicator |
|--------|-----------|
| Accounting policies | Aggressive revenue recognition |
| Restatements | History of restatements |
| Auditor relations | Frequent auditor changes |
| Management attitude | Disputes with auditors |
| Ethics culture | Weak tone at the top |

### Interpretation

| Score | Risk Level |
|-------|------------|
| 0-30% | LOW |
| 31-60% | MODERATE |
| 61-100% | HIGH |

---

## 7. Combined Risk Score

### Calculation

The overall risk score combines individual model outputs:

```
Overall = w1*Beneish + w2*Altman + w3*Piotroski + w4*Benford + w5*FraudTriangle
```

### Default Weights

| Model | Weight | Rationale |
|-------|--------|-----------|
| Beneish M-Score | 30% | Direct manipulation detection |
| Altman Z-Score | 25% | Financial distress indicator |
| Piotroski F-Score | 15% | Financial strength |
| Fraud Triangle | 15% | Behavioral factors |
| Benford's Law | 5% | Pattern detection |
| Red Flags | 10% | Qualitative indicators |

### Risk Levels

| Score | Level | Action |
|-------|-------|--------|
| 0-25 | LOW | Minimal concern |
| 26-50 | MODERATE | Further investigation recommended |
| 51-75 | HIGH | Significant red flags |
| 76-100 | CRITICAL | Strong manipulation indicators |

---

## 8. Limitations

### Model Limitations

1. **Historical basis:** Models based on past fraud may miss new schemes
2. **Industry variations:** Some industries naturally show different patterns
3. **Size effects:** Large vs. small companies behave differently
4. **International:** Models developed for US GAAP

### Data Limitations

1. **XBRL coverage:** Not all companies use same concepts
2. **Timing:** Recent filings may lack complete data
3. **Restatements:** Historical data may change

### Important Disclaimers

1. **Not definitive:** High scores don't prove fraud
2. **False positives:** Legitimate companies may score high
3. **False negatives:** Sophisticated fraud may evade detection
4. **Professional advice:** Consult experts for investment decisions

---

## References

1. Beneish, M.D. (1999). "The Detection of Earnings Manipulation." Financial Analysts Journal.
2. Altman, E.I. (1968). "Financial Ratios, Discriminant Analysis and the Prediction of Corporate Bankruptcy." Journal of Finance.
3. Piotroski, J.D. (2000). "Value Investing: The Use of Historical Financial Statement Information." Journal of Accounting Research.
4. Nigrini, M.J. (2012). Benford's Law: Applications for Forensic Accounting. Wiley.
5. Cressey, D.R. (1953). Other People's Money. Free Press.

---

**Version:** 2.1.2 | **Date:** January 2026
