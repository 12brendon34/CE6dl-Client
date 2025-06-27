#pragma once
#include "Core/Sdk/Engine/engine.h"
#include "Core/Sdk/Engine/CMaterialMgr.h"
#include "Core/Sdk/Engine/resource.h"

namespace Loader {

    struct SubMod {
        enum class Type {
            ASI = 1,
            PAK,
            RPACK,
            TINY_RPACK,
            MP
        };

        HMODULE ModHandle;
        std::string ModName;
        std::string ModPath;
        Type ModType;

        SubMod(std::string name, std::string path, Type type)
            : ModName(std::move(name)), ModPath(std::move(path)), ModType(type) {}
    };

    struct Mod {
        std::string ModName;                // Display name
        std::vector<SubMod> SubMods;        // Associated submods
        bool IsEnabled = true;              // Enabled toggle
        bool IsPriority = false;            // Overwrite base game rpacks

        Mod(std::string name) : ModName(std::move(name)) {}
    };


    using T_PreInitialize = void (*)(std::string ModDir);
    using T_PostInitialize = void (*)(IGame* pIGame);
    using T_GetPluginName = const char* (*)(void);

    void IndexMods();

    void LoadNativeMods();
    void LoadModPaks();

    void LoadResourcePaks(CResourceLoadingRuntime* s_ResourceLoadingRuntime, bool priority_only = false);
    //void LoadTinyResourcePaks(AssetManager* s_AssetManagerImpl);
    void LoadTinyResourcePaks(IGame* pGame);
    void LoadMaterialPacks(CMaterialMgr* s_MaterialMgr);

    void PreInitialize();
    void PostInitialize(IGame* pIGame);

    /*

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
    void LoadResourcePaks(AssetManager* s_AssetManagerImpl);
    */
}