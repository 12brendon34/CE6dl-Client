#include <pch.h>
#include "Console.h"

namespace Utils
{
    void InitConsole()
    {
        FILE* fp;
        if (!AttachConsole(ATTACH_PARENT_PROCESS)) {
            AllocConsole();
        }
        freopen_s(&fp, "CONOUT$", "w", stdout);
        freopen_s(&fp, "CONOUT$", "w", stderr);
    }
}
