//
// Created by Brendon on 1/26/2026.
//

#pragma once
#include <filesystem>
#include "ModInstance.h"

inline std::filesystem::path DefaultModsDirectory() {
    return {"Mods"};
}

class Loader {
public:
    explicit Loader(std::filesystem::path root = DefaultModsDirectory()) : m_Root(std::move(root)) {}

    [[nodiscard]] bool EnsureModsDirectoryExists() const;
    void IndexMods();
    void ParseMods(std::vector<std::filesystem::path> modPaths);
    void LoadPhase(ModLoadPhase phase) const;
    void UnLoadPhase(ModLoadPhase phase) const;

    std::filesystem::path m_Root;
    std::vector<Mod> m_Mods;
};
