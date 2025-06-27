#pragma once

namespace Utils {
    //Returns module base address
    FARPROC GetProcAddress(HMODULE hModule, LPCSTR lpProcName);
    //echos sig scanner
    unsigned long long findSig(HMODULE hModule, const char* szSignature);
}
