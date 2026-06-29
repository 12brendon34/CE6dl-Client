//
// Created by Brendon on 1/12/2026.
//

//this is not actually from chrome engine
//just a helper
#pragma once
#include <cstdio>
#include <cstdarg>
#include <mutex>

#ifdef _DEBUG
#include <windows.h>

inline void dbgprintf_impl(const char* func, int line, const char* format, ...) {
    static std::mutex log_mutex;
    static FILE* log_file = nullptr;
    
    std::lock_guard<std::mutex> lock(log_mutex);
    
    if (!log_file) {
#if defined(_MSC_VER)
        fopen_s(&log_file, "dlce_debug.log", "a");
#else
        log_file = fopen("dlce_debug.log", "a");
#endif
    }

    char prefix[256];
    SYSTEMTIME st;
    GetLocalTime(&st);
    snprintf(prefix, sizeof(prefix), "[%02d:%02d:%02d.%03d] [%s:%d] ", st.wHour, st.wMinute, st.wSecond, st.wMilliseconds, func, line);

    va_list args;
    va_start(args, format);
    fprintf(stdout, "%s", prefix);
    vfprintf(stdout, format, args);
    va_end(args);

    if (log_file) {
        va_start(args, format);
        fprintf(log_file, "%s", prefix);
        vfprintf(log_file, format, args);
        va_end(args);
        fflush(log_file);
    }
}

#define dbgprintf(fmt, ...) dbgprintf_impl(__FUNCTION__, __LINE__, fmt, ##__VA_ARGS__)
#else
#define dbgprintf(fmt, ...) ((void)0)
#endif
