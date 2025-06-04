#pragma once

namespace Utils {
    //Returns module base address
    FARPROC GetProcAddress(HMODULE hModule, LPCSTR lpProcName);
}
