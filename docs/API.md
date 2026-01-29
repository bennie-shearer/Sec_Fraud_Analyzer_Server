# SEC EDGAR Fraud Analyzer - API Reference

**Version:** 2.1.2  
**Author:** Bennie Shearer (Retired)

**DISCLAIMER: This project is NOT funded, endorsed, or approved by the U.S. Securities and Exchange Commission (SEC).**

---

## Table of Contents

1. [Overview](#1-overview)
2. [Base URL](#2-base-url)
3. [Endpoints](#3-endpoints)
4. [Response Format](#4-response-format)
5. [Error Handling](#5-error-handling)
6. [Rate Limiting](#6-rate-limiting)
7. [Examples](#7-examples)

---

## 1. Overview

RESTful HTTP API for analyzing SEC filings.

**Content-Type:** application/json  
**Encoding:** UTF-8

---

## 2. Base URL

```
http://localhost:8080/api
```

Port configurable via `--port` argument.

---

## 3. Endpoints

### 3.1 Health Check

**GET** `/api/health`

```json
{
  "status": "ok",
  "version": "2.1.2",
  "uptime_seconds": 3600
}
```

### 3.2 Analyze Company

**GET** `/api/analyze?ticker={ticker}&years={years}`

| Parameter | Type | Required | Default |
|-----------|------|----------|---------|
| ticker | string | Yes | - |
| years | integer | No | 5 |

**Response:**
```json
{
  "company": {
    "name": "Apple Inc.",
    "ticker": "AAPL",
    "cik": "0000320193"
  },
  "overall_risk": "LOW",
  "overall_score": 25.5,
  "models": {
    "beneish": { "m_score": -2.45, "risk_level": "LOW" },
    "altman": { "z_score": 4.82, "risk_level": "LOW" },
    "piotroski": { "f_score": 7, "risk_level": "LOW" }
  },
  "filings_analyzed": 17
}
```

### 3.3 List Filings

**GET** `/api/filings?ticker={ticker}`

### 3.4 Company Search

**GET** `/api/search?q={query}`

### 3.5 CIK Lookup

**GET** `/api/cik/{cik}`

---

## 4. Response Format

### Success

```json
{
  "status": "success",
  "data": { ... }
}
```

### Error

```json
{
  "status": "error",
  "error": {
    "code": "COMPANY_NOT_FOUND",
    "message": "Company not found: XYZ"
  }
}
```

---

## 5. Error Handling

| Code | HTTP Status | Description |
|------|-------------|-------------|
| COMPANY_NOT_FOUND | 404 | Ticker not found |
| INVALID_TICKER | 400 | Invalid format |
| SEC_API_ERROR | 502 | SEC unavailable |
| RATE_LIMITED | 429 | Too many requests |

---

## 6. Rate Limiting

- SEC limit: 10 requests/second
- Client limit: 60 requests/minute

---

## 7. Examples

```bash
# Analyze Apple
curl "http://localhost:8080/api/analyze?ticker=AAPL"

# Search companies
curl "http://localhost:8080/api/search?q=microsoft"

# List filings
curl "http://localhost:8080/api/filings?ticker=MSFT"
```

---

**Version:** 2.1.2 | **Date:** January 2026
