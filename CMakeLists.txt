# SEC EDGAR Fraud Analyzer - CMake Build Configuration
# Version: 2.1.2
# Author: Bennie Shearer (Retired)
#
# DISCLAIMER: This project is NOT funded, endorsed, or approved by the
# U.S. Securities and Exchange Commission (SEC).
#
# Cross-platform build for Windows, Linux, and macOS

cmake_minimum_required(VERSION 3.16)

project(Sec_Fraud_Analyzer_Server
    VERSION 2.1.2
    DESCRIPTION "SEC EDGAR Fraud Analyzer Server- Financial Forensics Tool"
    LANGUAGES CXX
)

# C++20 Standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Source files
set(SOURCES
    src/main.cpp
    src/http_server.cpp
    src/sec_fetcher.cpp
    src/analyzer.cpp
    src/exporter.cpp
    src/cache.cpp
    src/models/beneish.cpp
    src/models/altman.cpp
    src/models/piotroski.cpp
    src/models/fraud_triangle.cpp
    src/models/benford.cpp
)

# Header files (for IDE support)
set(HEADERS
    include/sec_analyzer/version.h
    include/sec_analyzer/types.h
    include/sec_analyzer/util.h
    include/sec_analyzer/logger.h
    include/sec_analyzer/json.h
    include/sec_analyzer/cache.h
    include/sec_analyzer/http_server.h
    include/sec_analyzer/sec_fetcher.h
    include/sec_analyzer/analyzer.h
    include/sec_analyzer/exporter.h
    include/sec_analyzer/models/beneish.h
    include/sec_analyzer/models/altman.h
    include/sec_analyzer/models/piotroski.h
    include/sec_analyzer/models/fraud_triangle.h
    include/sec_analyzer/models/benford.h
)

# Create executable
add_executable(sec_fraud_analyzer ${SOURCES} ${HEADERS})

# Platform-specific settings
if(WIN32)
    # Windows: Link Winsock2 and WinHTTP
    target_link_libraries(sec_fraud_analyzer ws2_32 winhttp)
    target_compile_definitions(sec_fraud_analyzer PRIVATE
        _WIN32_WINNT=0x0601
        WIN32_LEAN_AND_MEAN
        NOMINMAX
    )
    # Suppress deprecation warnings for POSIX functions
    target_compile_definitions(sec_fraud_analyzer PRIVATE
        _CRT_SECURE_NO_WARNINGS
    )
elseif(APPLE)
    # macOS: No special libraries needed
    find_package(Threads REQUIRED)
    target_link_libraries(sec_fraud_analyzer Threads::Threads)
else()
    # Linux: Link pthread
    find_package(Threads REQUIRED)
    target_link_libraries(sec_fraud_analyzer Threads::Threads)
endif()

# Compiler-specific flags
if(MSVC)
    target_compile_options(sec_fraud_analyzer PRIVATE
        /W4
        /permissive-
        /Zc:__cplusplus
        /utf-8
    )
else()
    target_compile_options(sec_fraud_analyzer PRIVATE
        -Wall
        -Wextra
        -Wpedantic
        -Wno-unused-parameter
    )
    
    # Optimization for release builds
    if(CMAKE_BUILD_TYPE STREQUAL "Release")
        target_compile_options(sec_fraud_analyzer PRIVATE -O3)
    endif()
endif()

# Installation
install(TARGETS sec_fraud_analyzer
    RUNTIME DESTINATION bin
)

install(DIRECTORY ${CMAKE_SOURCE_DIR}/../web/
    DESTINATION share/sec_fraud_analyzer/web
)

# Print configuration summary
message(STATUS "")
message(STATUS "SEC EDGAR Fraud Analyzer v${PROJECT_VERSION}")
message(STATUS "Author: Bennie Shearer (Retired)")
message(STATUS "")
message(STATUS "Configuration:")
message(STATUS "  C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "  Build Type: ${CMAKE_BUILD_TYPE}")
message(STATUS "  Platform: ${CMAKE_SYSTEM_NAME}")
message(STATUS "  Compiler: ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "")
