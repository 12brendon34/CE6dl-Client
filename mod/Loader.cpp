#include <pch.h>
#include "Loader.h"

namespace Loader {

    static std::vector<ModInfo> ModInfoList;

    std::string SetupModFolder(const std::string& subDir)
    {
        const std::string baseDir = Utils::GetWorkingDirectory();
        const std::string modsDir = baseDir + "Mods\\";
        const std::string subDirPath = modsDir + subDir + "\\";

        Utils::CreateFolder(modsDir);
        Utils::CreateFolder(subDirPath);

        return subDirPath;
    }

    void LoadNativeMods()
    {
        fs::path LibPath = SetupModFolder("Lib");

        for (const auto& entry : fs::directory_iterator(LibPath))
        {
            auto ext = Utils::str_tolower(entry.path().extension().string());
            auto c_str = entry.path().string().c_str();

            if (ext == ".asi" || ext == ".dll")
            {
                ModInfo currentMod;
                currentMod.ModName = entry.path().stem().string();
                currentMod.IsEnabled = true;
                currentMod.ModType = 0;
                currentMod.ModPath = c_str;
                ModInfoList.push_back(currentMod);
                if (LoadLibrary(c_str))
                    dbgprintf(">>Plugin loaded: %s\n", c_str);
                else
                    dbgprintf(">>Plugin error: %s\n", c_str);
            }
        }
    }

    void IndexMods()
    {
        auto PakDir = SetupModFolder("Paks");
        auto RpackDir = SetupModFolder("Rpacks");
        auto MPDir = SetupModFolder("MatPacks");

        //Filesystem::Add_Source(PakDir.c_str(), 7);
        Filesystem::Add_Source(RpackDir.c_str(), 7);
        Filesystem::Add_Source(MPDir.c_str(), 7);

        for (const auto& entry : fs::directory_iterator(PakDir)) 
        {
            if (Utils::str_tolower(entry.path().extension().string()) == ".pak")
            {
                ModInfo currentMod;
                currentMod.ModName = entry.path().stem().string();
                currentMod.IsEnabled = true;
                currentMod.ModType = 1;
                currentMod.ModPath = entry.path().string();
                ModInfoList.push_back(currentMod);
            }
        }

        for (const auto& entry : fs::directory_iterator(RpackDir))
        {
            auto ext = Utils::str_tolower(entry.path().extension().string());
            if (ext == ".rpack" || ext == ".rpaco" || ext == ".rpacz")
            {
                ModInfo currentMod;
                currentMod.ModName = entry.path().stem().string();
                currentMod.IsEnabled = true;
                currentMod.ModType = 2;
                currentMod.ModPath = entry.path().string();
                ModInfoList.push_back(currentMod);
            }
        }

        for (const auto& entry : fs::directory_iterator(MPDir))
        {
            if (Utils::str_tolower(entry.path().extension().string()) == ".mp")
            {
                ModInfo currentMod;
                currentMod.ModName = entry.path().stem().string();
                currentMod.IsEnabled = true;
                currentMod.ModType = 3;
                currentMod.ModPath = entry.path().string();
                ModInfoList.push_back(currentMod);
            }
        }
    }

    void LoadModPaks() {
        for (size_t i = 0; i < ModInfoList.size(); i++)
        {
            if (ModInfoList[i].ModType == 1)
            {
                auto cPak = ModInfoList[i].ModPath.c_str();
                Filesystem::Add_Source(cPak, 9);

                dbgprintf("Added Source : %s\n", cPak);
            }
        }
    }

    void LoadResorcePacks(Engine::AssetManager* s_AssetManagerImpl)
    {
        for (size_t i = 0; i < ModInfoList.size(); i++)
        {
            if (ModInfoList[i].ModType == 2)
            {
                auto cRpack = ModInfoList[i].ModPath.c_str();

                s_AssetManagerImpl->LoadAsset(cRpack, 256, NULL);

                dbgprintf("Added Rpack : %s\n", cRpack);
            }
        }
    }

    void LoadMaterialPacks(Engine::CMaterialMgr* s_MaterialMgr)
    {
        for (size_t i = 0; i < ModInfoList.size(); i++)
        {
            if (ModInfoList[i].ModType == 3)
            {
                auto cMatPack = ModInfoList[i].ModPath;

                cMatPack = Utils::RemoveSuffix(cMatPack, "_dx11.mp");
                s_MaterialMgr->LoadPack(cMatPack.c_str(), 1);//2 for local mp and 1 for built in or optimised? not sure, I'll go with 1

                dbgprintf("Added Mat Pack : %s\n", cMatPack);
            }
        }
    }
}
