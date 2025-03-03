#pragma once

#include "../SDK/Filesystem/filesystem_x64_rwdi.h"
#include "../SDK/Engine/engine_x64_rwdi.h"

namespace Loader {
    using T_PreInitialize = void (*)(void);
    using T_PostInitialize = void (*)(void);
    using T_GetPluginName = const char* (*)(void);

    struct ModInfo {
        std::string ModName;
        std::string ModPath;
        bool IsEnabled;
        enum {
            ASI = 1,
            PAK = 2,
            RPACK = 3,
            MP = 4
        } ModType;
    };

    std::string GetModFolderPath(const std::string& subDir);
    void ProcessModDirectory(const std::string& dir);
    void IndexMods();

    void LoadNativeMods();

    void PreInitialize();
    void PostInitialize();

    void LoadModPaks();
    void LoadResourcePaks(IGame* pGame);
}