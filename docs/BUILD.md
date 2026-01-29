# SEC EDGAR Fraud Analyzer - Build Guide

**Version:** 2.1.2  
**Author:** Bennie Shearer (Retired)

**DISCLAIMER: This project is NOT funded, endorsed, or approved by the U.S. Securities and Exchange Commission (SEC).**

---

## Table of Contents

1. [Prerequisites](#1-prerequisites)
2. [Windows Build](#2-windows-build)
3. [Linux Build](#3-linux-build)
4. [macOS Build](#4-macos-build)
5. [Command Line Build](#5-command-line-build)
6. [IDE Setup](#6-ide-setup)
7. [Troubleshooting](#7-troubleshooting)

---

## 1. Prerequisites

### All Platforms

- CMake 3.16 or higher
- C++20 compatible compiler
- Internet connection (for SEC API)

### Windows

- Visual Studio 2022 with C++ workload, OR
- MinGW-w64 with GCC 11+
- Windows SDK (for WinHTTP)

### Linux

- GCC 11+ or Clang 14+
- curl (for HTTP requests)
- Build essentials: `sudo apt install build-essential cmake curl`

### macOS

- Xcode Command Line Tools: `xcode-select --install`
- CMake: `brew install cmake` (or download from cmake.org)

---

## 2. Windows Build

### Using MinGW-w64 (Recommended for CLion)

```cmd
mkdir build
cd build
cmake -G "MinGW Makefiles" ..
cmake --build .
```

### Using MSVC (Visual Studio)

```cmd
mkdir build
cd build
cmake ..
cmake --build . --config Release
```

### Manual MinGW Build

```cmd
g++ -std=c++20 -O2 -Wall -Wextra -Wpedantic -Wno-unused-parameter ^
    -DNOMINMAX -DWIN32_LEAN_AND_MEAN -D_WIN32_WINNT=0x0601 ^
    -I./include -o sec_fraud_analyzer.exe ^
    src/*.cpp src/models/*.cpp ^
    -lws2_32 -lwinhttp
```

---

## 3. Linux Build

### Ubuntu/Debian

```bash
# Install prerequisites
sudo apt update
sudo apt install build-essential cmake curl

# Build
mkdir build && cd build
cmake ..
make -j$(nproc)
```

### Fedora/RHEL

```bash
# Install prerequisites
sudo dnf install gcc-c++ cmake curl make

# Build
mkdir build && cd build
cmake ..
make -j$(nproc)
```

---

## 4. macOS Build

```bash
# Install Xcode Command Line Tools
xcode-select --install

# Install CMake (if needed)
brew install cmake

# Build
mkdir build && cd build
cmake ..
make -j$(sysctl -n hw.ncpu)
```

---

## 5. Command Line Build

### Without CMake

**Linux/macOS:**
```bash
g++ -std=c++20 -O2 -Wall -Wextra -Wpedantic \
    -I./include -o sec_fraud_analyzer \
    src/*.cpp src/models/*.cpp \
    -lpthread
```

**Windows (MinGW):**
```cmd
g++ -std=c++20 -O2 -Wall -Wextra -Wpedantic ^
    -I./include -o sec_fraud_analyzer.exe ^
    src/*.cpp src/models/*.cpp ^
    -lws2_32 -lwinhttp
```

---

## 6. IDE Setup

### CLion (Recommended)

1. Open CLion
2. File -> Open -> Select project directory
3. CLion auto-detects CMakeLists.txt
4. Configure toolchain:
   - Windows: MinGW or Visual Studio
   - Linux: GCC
   - macOS: Clang
5. Build -> Build Project (Ctrl+F9)

### Visual Studio 2022

1. File -> Open -> CMake...
2. Select CMakeLists.txt
3. Select startup item: sec_fraud_analyzer.exe
4. Build -> Build All (Ctrl+Shift+B)

### Visual Studio Code

1. Install extensions: C/C++, CMake Tools
2. Open project folder
3. CMake Tools will detect CMakeLists.txt
4. Click Build in status bar

---

## 7. Troubleshooting

### Common Issues

**Error:** `concept is a reserved keyword`  
**Solution:** Fixed in v1.7.13+. Update to v2.1.2.

**Error:** `undefined reference to WinHttpOpen`  
**Solution:** Add `-lwinhttp` to link command (Windows only).

**Error:** `curl: command not found`  
**Solution:** Install curl: `sudo apt install curl`

**Error:** CMake version too old  
**Solution:** Upgrade CMake or download from cmake.org

### Clean Build

```bash
rm -rf build
mkdir build && cd build
cmake ..
make
```

### Verify Build

```bash
./sec_fraud_analyzer --version
# Output: SEC EDGAR Fraud Analyzer v2.1.2

./sec_fraud_analyzer --help
# Shows command line options
```

---

**Version:** 2.1.2 | **Date:** January 2026
