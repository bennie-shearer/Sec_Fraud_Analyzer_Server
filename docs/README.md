# SEC EDGAR Fraud Analyzer - Server

**Version:** 2.1.2  
**Author:** Bennie Shearer (Retired)  
**License:** MIT

---

## Disclaimer

**This project is NOT funded, endorsed, or approved by the U.S. Securities and Exchange Commission (SEC).**

For educational and research purposes only.

---

## Overview

Cross-platform C++20 server for SEC EDGAR financial fraud detection.

---

## Features

- Five fraud detection models (Beneish, Altman, Piotroski, Benford, Fraud Triangle)
- Real-time SEC EDGAR API integration
- XBRL financial data extraction
- RESTful HTTP API
- Zero external dependencies

---

## Build Instructions

### Windows (MinGW)

```cmd
mkdir build && cd build
cmake -G "MinGW Makefiles" ..
cmake --build .
```

### Windows (MSVC)

```cmd
mkdir build && cd build
cmake ..
cmake --build . --config Release
```

### Linux/macOS

```bash
mkdir build && cd build
cmake ..
make -j$(nproc)
```

---

## Run

```bash
./sec_fraud_analyzer --port 8080 --log-level info
```

---

## Command Line Options

| Option | Description |
|--------|-------------|
| --port | Server port (default: 8080) |
| --log-level | debug, info, warning, error |
| --log-file | Log file path |
| --quiet | Suppress console output |

---

## Platform Support

| Platform | Compiler | HTTP Client |
|----------|----------|-------------|
| Windows 10/11 | MSVC 2022 | WinHTTP |
| Windows 10/11 | MinGW-w64 | WinHTTP |
| Ubuntu 22.04+ | GCC 11+ | System curl |
| macOS 12+ | Clang 14+ | System curl |

---

## Documentation

See `docs/` directory for:
- BACKGROUND.md - Project history and design
- API.md - REST API reference
- BUILD.md - Detailed build instructions
- USER_GUIDE.md - Usage instructions
- MODELS.md - Fraud detection model details
- TROUBLESHOOTING.md - Common issues and solutions
- CONTRIBUTING.md - Contribution guidelines
- SECURITY.md - Security policy
- CHANGELOG.md - Version history

---

## Limitations

1. **Data Availability**: Analysis depends on SEC EDGAR data availability
2. **XBRL Coverage**: Not all filings have complete XBRL data
3. **Industry Variations**: Model thresholds may vary by industry
4. **Historical Data**: Older filings may lack standardized data

---

## Acknowledgments

- **Walter Hamscher** - Mentor and XBRL expert
- **SEC EDGAR** - Financial data source
- **Academic researchers** - Beneish, Altman, Piotroski, Cressey, Benford
- **CLion** by JetBrains s.r.o.
- **Claude** by Anthropic PBC

---

**Version:** 2.1.2 | **Date:** January 2026
