#pragma once
#include "Core/Sdk/Engine/engine.h"
#include "Core/Sdk/Engine/resource.h"

namespace Loader {
    struct SubMod {
        std::string ModName;
        std::string ModPath;

        enum ModTypeEnum {
            ASI = 1,
            PAK = 2,
            RPACK = 3,
            TINY_RPACK = 4,
            MP = 5
        } ModType;
    };

    struct Mod {
        std::string ModName; //Display name for future use
        std::vector<SubMod> SubMods;  // <-- List of associated submods
        bool IsEnabled; //future toggle
    };

    using T_PreInitialize = void (*)(void);
    using T_PostInitialize = void (*)(IGame* pIGame);
    using T_GetPluginName = const char* (*)(void);

    void IndexMods();

    void LoadNativeMods();
    void LoadModPaks();

    CResourceDataPack* LoadResourcePaks(CResourceLoadingRuntime* s_ResourceLoadingRuntime);
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