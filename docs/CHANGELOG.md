# SEC EDGAR Fraud Analyzer - Changelog

**Version:** 2.1.2  
**Author:** Bennie Shearer (Retired)

**DISCLAIMER: This project is NOT funded, endorsed, or approved by the U.S. Securities and Exchange Commission (SEC).**

---

## [2.1.2] - 2026-01-23

### Added
- Limitations section to all documentation:
  1. Data Availability: Analysis depends on SEC EDGAR data availability
  2. XBRL Coverage: Not all filings have complete XBRL data
  3. Industry Variations: Model thresholds may vary by industry
  4. Historical Data: Older filings may lack standardized data

---

## [2.1.1] - 2026-01-23

### Added
- Acknowledgments section to all documentation:
  - Walter Hamscher - Mentor and XBRL expert
  - SEC EDGAR - Financial data source
  - Academic researchers - Beneish, Altman, Piotroski, Cressey, Benford
  - CLion by JetBrains s.r.o.
  - Claude by Anthropic PBC

---

## [2.1.0] - 2026-01-23

### Added
- CONTRIBUTING.md - Contribution guidelines and code style
- SECURITY.md - Security policy and vulnerability reporting
- TROUBLESHOOTING.md - Common issues and solutions
- MODELS.md - Detailed fraud detection model documentation
- .gitignore for server (C++) and web (JS) directories
- Improved inline documentation

### Changed
- Version bump to 2.1.0
- Enhanced documentation suite

---

## [2.0.0] - 2026-01-23

### Added
- Comprehensive BACKGROUND.md with Table of Contents covering:
  - History of Financial Fraud Detection Systems
  - Purpose and ecosystem context
  - Design philosophy
- Complete documentation suite (README, API, BUILD, USER_GUIDE)
- SEC disclaimer added to ALL files: "NOT funded, endorsed, or approved by the U.S. SEC"
- Separate README for server and web packages

### Changed
- Major version bump to 2.0.0
- Fixed year from 2025 to 2026 in all documents
- Web package no longer includes BUILD.md (not needed for HTML/CSS/JS)
- Replaced Unicode characters with ASCII-safe alternatives

### Fixed
- Documentation consistency
- Version synchronization across all files

---

## [1.7.14] - 2026-01-23

### Fixed
- Ticker normalization: BRK.A converts to BRK-A

---

## [1.7.13] - 2026-01-23

### Fixed
- Toolbar icons (18px to 22px)
- Revenue/Net Income $0.00 - implemented XBRL fetching
- C++20 keyword: `concept` to `concept_name`

---

## [1.7.12] - 2026-01-22

### Changed
- Author references to "(Retired)"

---

## [1.7.11] - 2026-01-22

### Fixed
- SEC User-Agent requirement (added email)

---

## [1.7.10] - 2026-01-22

### Added
- Linux/macOS HTTP client (system curl)

---

## [1.7.9] - 2026-01-22

### Added
- Windows WinHTTP implementation

---

## [1.7.5-1.7.8] - 2026-01-22

### Fixed
- Various compilation and linker issues
- Adjustable logging system

---

## [1.7.0] - 2026-01-22

### Added
- Initial release
- Five fraud detection models
- Web client with responsive UI
- C++20 HTTP server
- SEC EDGAR API integration

---

## Version Numbering

MAJOR.MINOR.PATCH (Semantic Versioning)

- **MAJOR**: Incompatible API changes
- **MINOR**: New functionality
- **PATCH**: Bug fixes

---

**Version:** 2.1.2 | **Date:** January 2026
