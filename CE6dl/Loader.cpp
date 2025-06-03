#include <pch.h>
#include "Loader.h"
//#include "Core/Sdk/Engine/engine.h"
//#include "Core/Sdk/Engine/resource.h"
#include "Core/Util/Directory.h"
#include "Core/Util/String.h"
#include "Hooks.h"
#include "Core/Sdk/Filesystem/Filesystem.h"


namespace Loader {
    std::vector<HMODULE> NativeMods;
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
        Utils::CreateFolder(ModsPath);

        path GlobalPaksPath = ModsPath / "GlobalPaks"; //for unsupported mod paks
        path TinyRpacksPath = ModsPath / "TinyRpacks"; //for mod developers


        /*
            MODS
            │
            └───ExampleMod
                │   Data2.pak
                │
                └───Data
                        Textures_PC.rpack
                        local_dx11.mp
        */


        for (const auto& entry : directory_iterator(ModsPath)) {
            path entryPath = entry.path();

            if (!is_directory(entryPath))
                continue;

            // Special mod folders
            if (entryPath == GlobalPaksPath) {
                Mod mod("GlobalPaks");
                ProcessModFolder(mod, entryPath, SubMod::Type::PAK, ".pak");
                if (!mod.SubMods.empty())
                    ModList.push_back(std::move(mod));
                continue;
            }

            if (entryPath == TinyRpacksPath) {
                Mod mod("TinyRpacks");
                ProcessModFolder(mod, entryPath, SubMod::Type::TINY_RPACK, ".rpack");
                if (!mod.SubMods.empty())
                    ModList.push_back(std::move(mod));
                continue;
            }

            // Regular mod folder
            Mod mod(entryPath.filename().string());
            auto moddata = entryPath / "data";

            ProcessModFolder(mod, entryPath, SubMod::Type::PAK, ".pak");
            ProcessModFolder(mod, entryPath, SubMod::Type::ASI, ".dll");
            ProcessModFolder(mod, entryPath, SubMod::Type::ASI, ".asi");

            if (exists(moddata) && is_directory(moddata)) {
                fs::add_source(moddata.string().c_str(), static_cast<FFSAddSourceFlags::ENUM>(7));
                ProcessModFolder(mod, moddata, SubMod::Type::RPACK, ".rpack");
                ProcessModFolder(mod, moddata, SubMod::Type::MP, ".mp");
            }

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
                NativeMods.push_back(HModule);
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

    void LoadResourcePaks(CResourceLoadingRuntime* s_ResourceLoadingRuntime) {
        for (const auto& modInfo : ModList) {
            for (const auto& subModInfo : modInfo.SubMods) {
                if (subModInfo.ModType != SubMod::Type::RPACK)
                    continue;

                auto packname = Utils::RemoveSuffix(subModInfo.ModPath, "_pc.rpack");

                PackLoader::Load(
                    s_ResourceLoadingRuntime,
                    packname.c_str(),
                    nullptr,
                    EIsGlobalPack::No,
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
                s_MaterialMgr->LoadPack(matName.c_str(), 2); // 1 or 2, changes global vs local?
            }
        }
    }

    //callbacks for native mods
    void PreInitialize() {
        for (const auto& HModule : NativeMods) {
            if (!HModule) {
                MessageBoxA(nullptr, "Module handle is null!", "Error", MB_ICONERROR);
                return;
            }

            auto PreInitialize = (T_PreInitialize)GetProcAddress(HModule, "PreInitialize");
            if (PreInitialize)
                PreInitialize();
        }
    }

    void PostInitialize(IGame* pIGame) {
        for (const auto& HModule : NativeMods) {
            if (!HModule) {
                MessageBoxA(nullptr, "Module handle is null!", "Error", MB_ICONERROR);
                return;
            }

            auto PostInitialize = (T_PostInitialize)GetProcAddress(HModule, "PostInitialize");
            if (PostInitialize)
                PostInitialize(pIGame);
        }
    }

}