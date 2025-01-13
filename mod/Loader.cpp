#include <pch.h>
#include "Loader.h"
#include "../engine/Link.h"

namespace Loader {

    static std::vector<ModInfo> ModInfoList;

    std::string CreateModsFolder() 
    {
        auto RootDL = Utils::GetWorkingDirectory();

        auto modsPath = RootDL + "Mods\\";
        auto subPath = modsPath + "Paks\\";

        std::cout << "Mods Path: " << modsPath << std::endl;
        std::cout << "Subfolder Path: " << subPath << std::endl;

        Utils::CreateFolder(modsPath);
        Utils::CreateFolder(subPath);

        return subPath;
    }

    void IndexPaks() 
    {
        auto PaksFolder = CreateModsFolder();

        for (const auto& entry : fs::directory_iterator(PaksFolder))
        {
            if (Utils::str_tolower(entry.path().extension().string()) == ".pak")
            {
                ModInfo CurrentMod;
                CurrentMod.ModName = L"PlaceHolder";
                CurrentMod.IsEnabled = true;
                CurrentMod.ModType = 0;
                CurrentMod.ModPath = entry.path().string();
                std::cout << CurrentMod.ModPath << std::endl;
                ModInfoList.push_back(CurrentMod);
            }
        }
    }

    void LoadModPaks() {
        for (size_t i = 0; i < ModInfoList.size(); i++)
        {
            if (ModInfoList[i].ModType == 0)
            {
                auto cPak = ModInfoList[i].ModPath.c_str();
                Filesystem::Add_Source(cPak, 9);

                dbgprintf("Added Source : %s\n", cPak);
            }
        }
    }
}
