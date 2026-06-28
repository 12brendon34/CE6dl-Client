//
// Created by Brendon on 1/12/2026.
//

//this is not actually from chrome engine
//just a helper
#pragma once
#include <cstdio>
#include <cstdarg>

inline void dbgprintf(const char* format, ...) {
    va_list args;
    va_start(args, format);
    vfprintf(stdout, format, args);
    va_end(args);

    FILE* logFile;
    if (fopen_s(&logFile, "dlce_debug.log", "a") == 0) {
        va_start(args, format);
        vfprintf(logFile, format, args);
        va_end(args);
        fclose(logFile);
    }
}
