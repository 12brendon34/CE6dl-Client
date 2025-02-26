#pragma once

#include "Filesystem/filesystem_x64_rwdi.h"
#include "Engine/engine_x64_rwdi.h"

namespace Loader {

    struct ModInfo {
        std::string ModName;
        std::string ModPath;
        bool IsEnabled;
        enum {
            PAK = 1,
            RPACK = 2,
            ASI = 3,
            MP = 4
        } ModType;
    };

    std::string GetModFolderPath(const std::string& subDir);
    void ProcessModDirectory(const std::string& dir);
    void IndexMods();
    void LoadModPaks();
    void LoadResourcePaks(AssetManager* s_AssetManagerImpl);
}