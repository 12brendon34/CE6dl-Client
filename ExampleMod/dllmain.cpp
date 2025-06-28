#include <pch.h>
#include "PluginInfo.h"
#include "Hooks/HookManager.h"
#include "Hooks/UIOptionSliderHook.h"
#include "Hooks/MenuOptionsGameHook.h"
#include "Core/Util/IniConfig.h"

class IGame;
const char* const kPluginName = "SimpleFov";

extern "C" __declspec(dllexport) const char* GetPluginName() {
    return kPluginName;
}

extern "C" __declspec(dllexport) void PreInitialize(std::string ModPath) {
    dbgprintf("[%s] PreInitialize\n", kPluginName);

    std::filesystem::path modDir = std::filesystem::path(ModPath).parent_path();
    std::filesystem::path iniPath = modDir / (std::string(kPluginName) + ".ini");

    if (!std::filesystem::exists(iniPath)) {
        std::ofstream defaultConfig(iniPath);
        if (defaultConfig.is_open()) {
            defaultConfig << "maxfov=" << g_maxFov << "\n";
            defaultConfig.close();
            dbgprintf("[%s] Created default ini at %s\n", kPluginName, iniPath.string().c_str());
        }
        else {
            dbgprintf("[%s] Failed to create ini at %s\n", kPluginName, iniPath.string().c_str());
        }
    }

    auto config = Utils::ReadSimpleIni(iniPath);
    auto it = config.find("maxfov");
    if (it != config.end()) {
        try {
            g_maxFov = std::stoi(it->second);
            dbgprintf("[%s] Loaded maxfov from ini: %d\n", kPluginName, g_maxFov);
        }
        catch (...) {
            dbgprintf("[%s] Invalid maxfov value in ini. Using default: %d\n", kPluginName, g_maxFov);
        }
    }
    else {
        dbgprintf("[%s] maxfov not found in ini. Using default: %d\n", kPluginName, g_maxFov);
    }

    //enable hooks
    HookManager::get().add(std::make_unique<UIOptionSliderHook>());
    HookManager::get().add(std::make_unique<MenuOptionsGameHook>());
}

extern "C" __declspec(dllexport) void PostInitialize(IGame* pIGame) {
    dbgprintf("[%s] PostInitialize\n", kPluginName);
    dbgprintf("IGame Ptr: %p\n", pIGame);
}
