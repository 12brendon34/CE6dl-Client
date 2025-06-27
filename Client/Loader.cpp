#include <pch.h>
#include "Loader.h"
//#include "Core/Sdk/Engine/engine.h"
//#include "Core/Sdk/Engine/resource.h"
#include "Core/Util/Directory.h"
#include "Core/Util/UString.h"
//#include "Hooks.h"
#include "Core/Sdk/Filesystem/Filesystem.h"
#include "Core/Util/IniConfig.h"
#include "Hooks/PackLoader.h"


namespace Loader {
    //std::vector<HMODULE> NativeMods;
    static std::vector<Mod> ModList;

    void ProcessModFolder(Mod& mod, const std::filesystem::path& folderPath, SubMod::Type modType, const std::string& expectedExtension) {
        for (const auto& entry : std::filesystem::directory_iterator(folderPath)) {
            const auto& filePath = entry.path();

            if (!entry.is_regular_file())
                continue;

            if (Utils::str_tolower(filePath.extension().string()) != expectedExtension)
                continue;

            std::string subModName = filePath.stem().string();
            std::string subModPath = filePath.string();

            mod.SubMods.emplace_back(subModName, subModPath, modType);
        }
    }

    void IndexMods() {
        using namespace std::filesystem;

        path ModsPath = Utils::GetWorkingDirectory() / "Mods";
        path LoadOrderPath = ModsPath / "load_order.ini";
        Utils::CreateFolder(ModsPath);

        std::vector<std::string> discoveredMods;
        for (const auto& entry : directory_iterator(ModsPath)) {
            if (entry.is_directory()) {
                std::string name = entry.path().filename().string();
                if (name != "GlobalPaks" && name != "TinyRpacks")
                    discoveredMods.push_back(name);
            }
        }

        if (!exists(LoadOrderPath)) {
            std::ofstream iniOut(LoadOrderPath);
            for (const auto& modName : discoveredMods)
                iniOut << modName << "\n";
            iniOut.close();
        }

        std::vector<std::string> loadOrder;
        std::ifstream iniIn(LoadOrderPath);
        std::string line;
        while (std::getline(iniIn, line)) {
            line.erase(0, line.find_first_not_of(" \t\r\n"));
            line.erase(line.find_last_not_of(" \t\r\n") + 1);
            if (!line.empty())
                loadOrder.push_back(line);
        }

        for (const auto& modFolder : loadOrder) {
            path modPath = ModsPath / modFolder;
            if (!exists(modPath) || !is_directory(modPath))
                continue;

            Mod mod(modFolder);

            path configPath = modPath / "modinfo.ini";
            if (!exists(configPath)) {
                std::ofstream defaultConfig(configPath);
                defaultConfig << "enabled=true\n";
                defaultConfig << "priority=false\n";
                defaultConfig.close();
            }

            auto config = Utils::ReadSimpleIni(configPath);
            if (config["enabled"] == "false" || config["enabled"] == "0") {
                continue; // Skip disabled mods
            }
            if (config["priority"] == "true" || config["priority"] == "1") {
                mod.IsPriority = true;
            }

            ProcessModFolder(mod, modPath, SubMod::Type::PAK, ".pak");
            ProcessModFolder(mod, modPath, SubMod::Type::ASI, ".dll");
            ProcessModFolder(mod, modPath, SubMod::Type::ASI, ".asi");

            path moddata = modPath / "data";
            if (exists(moddata) && is_directory(moddata)) {
                fs::add_source(moddata.string().c_str(), static_cast<FFSAddSourceFlags::ENUM>(7));
                ProcessModFolder(mod, moddata, SubMod::Type::RPACK, ".rpack");
                ProcessModFolder(mod, moddata, SubMod::Type::MP, ".mp");
            }

            if (!mod.SubMods.empty())
                ModList.push_back(std::move(mod));
        }

        //Global special folders
        path GlobalPaksPath = ModsPath / "GlobalPaks";
        if (exists(GlobalPaksPath)) {
            Mod mod("GlobalPaks");
            ProcessModFolder(mod, GlobalPaksPath, SubMod::Type::PAK, ".pak");
            if (!mod.SubMods.empty())
                ModList.push_back(std::move(mod));
        }

        path TinyRpacksPath = ModsPath / "TinyRpacks";
        if (exists(TinyRpacksPath)) {
            Mod mod("TinyRpacks");
            ProcessModFolder(mod, TinyRpacksPath, SubMod::Type::TINY_RPACK, ".rpack");
            if (!mod.SubMods.empty())
                ModList.push_back(std::move(mod));
        }
    }

    void LoadNativeMods() {
        for (auto& modInfo : ModList) {
            for (auto& subModInfo : modInfo.SubMods) {
                if (subModInfo.ModType != SubMod::Type::ASI)
                    continue;

                const char* libname = subModInfo.ModPath.c_str();
                HMODULE HModule = LoadLibrary(libname);
                if (!HModule)
                    continue;

                auto GetPluginName = (T_GetPluginName)GetProcAddress(HModule, "GetPluginName");
                if (GetPluginName)
                    subModInfo.ModName = GetPluginName();

                dbgprintf("[Plugin] %s loaded: %s\n", modInfo.ModName.c_str(), subModInfo.ModPath.c_str());
                subModInfo.ModHandle = HModule;
            }
        }
    }


    void LoadModPaks() {
        for (const auto& modInfo : ModList) {
            for (const auto& subModInfo : modInfo.SubMods) {
                if (subModInfo.ModType != SubMod::Type::PAK)
                    continue;

                fs::add_source(subModInfo.ModPath.c_str(), static_cast<FFSAddSourceFlags::ENUM>(9));
            }
        }
    }

    void LoadResourcePaks(CResourceLoadingRuntime* s_ResourceLoadingRuntime, bool priority_only) {
        for (const auto& modInfo : ModList) {
            for (const auto& subModInfo : modInfo.SubMods) {
                if (subModInfo.ModType != SubMod::Type::RPACK)
                    continue;

                const bool isPriority = modInfo.IsPriority;

                // If we're only loading priority packs, skip non-priority
                if (priority_only && !isPriority)
                    continue;

                // If we're only loading non-priority packs, skip priority
                if (!priority_only && isPriority)
                    continue;

                auto packname = Utils::RemoveSuffix(subModInfo.ModPath, "_pc.rpack");

                std::cout << "Loading " << (isPriority ? "priority" : "non-priority")
                    << " pack: " << packname << std::endl;

                PackLoader::Load(
                    s_ResourceLoadingRuntime,
                    packname.c_str(),
                    nullptr,
                    EIsGlobalPack::Yes,
                    EIsContentPack::No,
                    EUseCachePartition::Yes,
                    EIsCrossLevelPack::Yes,
                    static_cast<EPackKind>(0)
                );
            }
        }
    }


    void LoadTinyResourcePaks(IGame* pIGame) {
        for (const auto& modInfo : ModList) {
            for (const auto& subModInfo : modInfo.SubMods) {
                if (subModInfo.ModType != SubMod::Type::TINY_RPACK)
                    continue;

                ttl::string_base<char> PackPath(subModInfo.ModPath.c_str());
                std::cout << &PackPath << std::endl;

                pIGame->LoadPack(PackPath, true, true, nullptr);
                dbgprintf("Added Rpack : %s\n", subModInfo.ModPath.c_str());
            }
        }
    }

    void LoadMaterialPacks(CMaterialMgr* s_MaterialMgr) {
        for (const auto& modInfo : ModList) {
            for (const auto& subModInfo : modInfo.SubMods) {
                if (subModInfo.ModType != SubMod::Type::MP)
                    continue;

                auto matName = Utils::RemoveSuffix(subModInfo.ModPath, "_dx11.mp");
                s_MaterialMgr->LoadPack(matName.c_str(), 1); // 1 or 2, changes global vs local?
            }
        }
    }

    //callbacks for native mods
    void PreInitialize() {
        for (const auto& modInfo : ModList) {
            for (const auto& subModInfo : modInfo.SubMods) {
                if (subModInfo.ModType != SubMod::Type::ASI)
                    continue;

                if (!subModInfo.ModHandle) {
                    MessageBoxA(nullptr, "Module handle is null!", "Error", MB_ICONERROR);
                    return;
                }

                auto PreInitialize = (T_PreInitialize)GetProcAddress(subModInfo.ModHandle, "PreInitialize");
                if (PreInitialize)
                    PreInitialize(subModInfo.ModPath);
            }
        }
    }

    void PostInitialize(IGame* pIGame) {
        for (const auto& modInfo : ModList) {
            for (const auto& subModInfo : modInfo.SubMods) {
                if (subModInfo.ModType != SubMod::Type::ASI)
                    continue;

                if (!subModInfo.ModHandle) {
                    MessageBoxA(nullptr, "Module handle is null!", "Error", MB_ICONERROR);
                    return;
                }

                auto PostInitialize = (T_PostInitialize)GetProcAddress(subModInfo.ModHandle, "PostInitialize");
                if (PostInitialize)
                    PostInitialize(pIGame);
            }
        }
    }
}