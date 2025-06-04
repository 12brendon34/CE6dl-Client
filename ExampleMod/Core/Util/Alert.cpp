#include <pch.h>
#include "Alert.h"

namespace Utils
{
    int Alert(const char* lpCaption, const char* lpText)
    {
        return ::MessageBoxA(nullptr, lpText, lpCaption, MB_OK);
    }

    void MsgBoxExit(UINT nType, LPCSTR lpCaption, LPCSTR sz, ...)
    {
        char ach[512];
        va_list args;
        va_start(args, sz);
        (void)wvsprintf(ach, sz, args);
        (void)MessageBox(nullptr, ach, lpCaption, nType);
        ExitProcess(0);
    }
}
