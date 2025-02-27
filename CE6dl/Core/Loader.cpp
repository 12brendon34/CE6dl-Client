#include <pch.h>
#include "Loader.h"

namespace Loader {

    std::string GetModFolderPath(const std::string& subDir)
    {
        const std::string baseDir = Utils::GetWorkingDirectory();
        const std::string modsDir = baseDir + "Mods\\";
        const std::string subDirPath = modsDir + subDir + "\\";

        if (!std::filesystem::exists(modsDir))
            Utils::CreateFolder(modsDir);

        if (!std::filesystem::exists(subDirPath))
            Utils::CreateFolder(subDirPath);

        return subDirPath;
    }

    static std::vector<ModInfo> ModInfoList;

    void ProcessModDirectory(const std::string& dir) {

        for (const auto& entry : std::filesystem::directory_iterator(dir)) {
            ModInfo currentMod;

            std::string ext = entry.path().extension().string();
            Utils::str_tolower(ext);

            currentMod.ModName = entry.path().stem().string();
            currentMod.ModPath = entry.path().string();
            currentMod.IsEnabled = true;

            if (ext == ".pak") {
                currentMod.ModType = ModInfo::PAK;
            }
            else if (ext == ".rpack" || ext == ".rpaco" || ext == ".rpacz") {
                currentMod.ModType = ModInfo::RPACK;
            }
            else if (ext == ".asi" || ext == ".dll") {
                currentMod.ModType = ModInfo::ASI;
            }
            else if (ext == ".mp") {
                currentMod.ModType = ModInfo::MP;
            }

            //add if recognised file type
            if (currentMod.ModType)
                ModInfoList.push_back(currentMod);
        }
    }

    void IndexMods()
    {
        auto pakPath = GetModFolderPath("Paks");
        auto rpackPath = GetModFolderPath("Rpacks");
        auto matpackPath = GetModFolderPath("MatPacks");

        fs::add_source(rpackPath.c_str(), (FFSAddSourceFlags::ENUM)7);
        fs::add_source(matpackPath.c_str(), (FFSAddSourceFlags::ENUM)7);

        ProcessModDirectory(pakPath);
        ProcessModDirectory(rpackPath);
        ProcessModDirectory(matpackPath);
    }

    void LoadModPaks()
    {
        for (const auto& modInfo : ModInfoList)
        {
            if (modInfo.ModType == ModInfo::PAK)
            {
                fs::add_source(modInfo.ModPath.c_str(), (FFSAddSourceFlags::ENUM)9);
                dbgprintf("Added Source : %s\n", modInfo.ModPath.c_str());
            }
        }
    }

    void LoadResourcePaks(AssetManager* s_AssetManagerImpl)
    {
        for (const auto& modInfo : ModInfoList)
        {
            if (modInfo.ModType == ModInfo::RPACK)
            {
                s_AssetManagerImpl->LoadAsset(modInfo.ModPath.c_str(), 256, NULL);
                dbgprintf("Added Rpack : %s\n", modInfo.ModPath.c_str());
            }
        }
    }

    std::vector<HMODULE> NativeMods;
    void LoadNativeMods()
    {
        for (const auto& modInfo : ModInfoList)
        {
            if (modInfo.ModType == ModInfo::ASI)
            {
                auto HModule = LoadLibrary(modInfo.ModPath.c_str());

                if (HModule) {
                    ModInfo currentMod;
                    auto GetPluginName = (T_GetPluginName)GetProcAddress(HModule, "GetPluginName");

                    if (GetPluginName)
                        currentMod.ModName = GetPluginName();
                    else
                        currentMod.ModName = "PLUGIN_NAME_UNSET"; //maybe change to dll file name + _unset

                    dbgprintf("[Plugin] %s loaded: %s\n", currentMod.ModName, modInfo.ModPath.c_str());
                    NativeMods.push_back(HModule);
                }
                else
                    dbgprintf("[Plugin] Loading Error: %s\n", modInfo.ModPath.c_str());
            }
        }
    }

    void PreInitialize() {

        for (const auto& HModule : NativeMods)
        {
            if (HModule == nullptr) {
                MessageBoxA(0, "Module handle is null!", "Error", MB_ICONERROR);
                return;
            }

            auto PreInitialize = (T_PreInitialize)GetProcAddress(HModule, "PreInitialize");

            if (PreInitialize)
                PreInitialize();
        }
    }


    void PostInitialize() {

        for (const auto& HModule : NativeMods)
        {
            if (HModule == nullptr) {
                MessageBoxA(0, "Module handle is null!", "Error", MB_ICONERROR);
                return;
            }

            auto PostInitialize = (T_PostInitialize)GetProcAddress(HModule, "PostInitialize");

            if (PostInitialize)
                PostInitialize();
        }
    }
}