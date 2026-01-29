# Contributing to SEC EDGAR Fraud Analyzer

**Version:** 2.1.2  
**Author:** Bennie Shearer (Retired)

**DISCLAIMER: This project is NOT funded, endorsed, or approved by the U.S. Securities and Exchange Commission (SEC).**

---

## Table of Contents

1. [Getting Started](#getting-started)
2. [Code Style](#code-style)
3. [Submitting Changes](#submitting-changes)
4. [Testing](#testing)
5. [Documentation](#documentation)

---

## Getting Started

### Prerequisites

**Server (C++20):**
- CMake 3.16+
- C++20 compiler (GCC 11+, Clang 14+, MSVC 2022)
- No external dependencies required

**Web Client:**
- Modern web browser
- No build tools required

### Building

```bash
cd server
mkdir build && cd build
cmake ..
make
```

---

## Code Style

### C++ Guidelines

1. **Naming Conventions:**
   - Classes: `PascalCase` (e.g., `SECFetcher`)
   - Functions: `snake_case` (e.g., `get_filings`)
   - Variables: `snake_case` (e.g., `filing_count`)
   - Constants: `UPPER_SNAKE_CASE` (e.g., `MAX_RETRIES`)
   - Member variables: `m_` prefix (e.g., `m_cache`)

2. **Formatting:**
   - 4-space indentation
   - Braces on same line for functions
   - 100 character line limit
   - Always use braces for if/for/while

3. **Comments:**
   - Use `//` for single-line comments
   - Use `/** */` for documentation comments
   - Document all public functions

4. **Headers:**
   - Include guards using `#ifndef`/`#define`/`#endif`
   - Group includes: standard library, project headers

### JavaScript Guidelines

1. **Use strict mode:** `'use strict';`
2. **camelCase for variables and functions**
3. **Semicolons required**
4. **Single quotes for strings**

---

## Submitting Changes

### Before Submitting

1. Verify build succeeds on all platforms
2. Run manual testing
3. Update documentation if needed
4. Update CHANGELOG.md
5. Verify version numbers are consistent

### Commit Messages

Format: `[component] Brief description`

Examples:
- `[server] Fix XBRL parsing for quarterly reports`
- `[web] Add dark mode toggle keyboard shortcut`
- `[docs] Update API documentation`

---

## Testing

### Manual Testing Checklist

**Server:**
- [ ] Builds without warnings on Windows (MSVC)
- [ ] Builds without warnings on Windows (MinGW)
- [ ] Builds without warnings on Linux (GCC)
- [ ] Builds without warnings on macOS (Clang)
- [ ] Server starts and responds to health check
- [ ] Analysis returns valid results for AAPL
- [ ] Analysis handles invalid ticker gracefully

**Web Client:**
- [ ] Loads in Chrome, Firefox, Edge, Safari
- [ ] Dark mode toggles correctly
- [ ] Demo mode works without server
- [ ] Export functions work (JSON, CSV, HTML)
- [ ] Keyboard shortcuts function

---

## Documentation

### Required Updates

When making changes, update:

1. **CHANGELOG.md** - Add entry for changes
2. **README.md** - If features change
3. **API.md** - If API changes
4. **USER_GUIDE.md** - If user-facing changes
5. **Inline comments** - For code changes

### Version Numbering

Follow Semantic Versioning (MAJOR.MINOR.PATCH):

- **MAJOR:** Breaking API changes
- **MINOR:** New features (backward compatible)
- **PATCH:** Bug fixes (backward compatible)

---

**Version:** 2.1.2 | **Date:** January 2026
