# Security Policy

**Version:** 2.1.2  
**Author:** Bennie Shearer (Retired)

**DISCLAIMER: This project is NOT funded, endorsed, or approved by the U.S. Securities and Exchange Commission (SEC).**

---

## Supported Versions

| Version | Supported |
|---------|-----------|
| 2.1.x   | Yes       |
| 2.0.x   | Yes       |
| < 2.0   | No        |

---

## Security Considerations

### Data Handling

1. **No Sensitive Data Storage:**
   - No user credentials stored
   - No personal information collected
   - All data sourced from public SEC EDGAR

2. **Network Security:**
   - HTTPS used for SEC API calls
   - No authentication required
   - Rate limiting implemented

3. **Input Validation:**
   - Ticker symbols sanitized
   - CIK numbers validated
   - JSON responses parsed safely

### Known Limitations

1. **Local Server:**
   - Default configuration binds to localhost only
   - Not designed for production deployment
   - No built-in authentication

2. **Cache:**
   - Cached data stored in memory
   - No encryption of cached data
   - Cache cleared on restart

---

## Reporting a Vulnerability

### How to Report

If you discover a security vulnerability:

1. **Do NOT open a public issue**
2. Document the vulnerability with steps to reproduce
3. Include your environment details (OS, compiler, browser)

### What to Include

- Description of the vulnerability
- Steps to reproduce
- Potential impact
- Suggested fix (if any)

### Response Timeline

- Acknowledgment: Within 48 hours
- Initial assessment: Within 7 days
- Fix timeline: Depends on severity

---

## Security Best Practices

### For Users

1. Run server on localhost only
2. Do not expose to public internet
3. Keep software updated
4. Verify SEC data against official sources

### For Developers

1. Validate all user input
2. Use safe JSON parsing
3. Implement rate limiting
4. Log security-relevant events
5. Follow secure coding guidelines

---

## Compliance

This project:

- Uses only public SEC EDGAR data
- Complies with SEC API usage guidelines
- Respects rate limiting requirements
- Includes required User-Agent headers

---

**Version:** 2.1.2 | **Date:** January 2026
