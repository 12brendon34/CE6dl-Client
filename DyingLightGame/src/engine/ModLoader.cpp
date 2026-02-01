//
// Created by Brendon on 1/26/2026.
//

#include "ModLoader.h"

#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

#include "engine/Debug.h"
#include "engine/filesystem/Filesystem.h"
using json = nlohmann::json;

bool Loader::EnsureModsDirectoryExists() const {
    if (!std::filesystem::exists(m_Root)) {
        try {
            std::filesystem::create_directories(m_Root);
            return true;
        } catch (const std::filesystem::filesystem_error &e) {
            dbgprintf("Failed to create mods directory: %s", e.what());
            return false;
        }
    }
    return true;
}

void Loader::ParseMods(std::vector<std::filesystem::path> modPaths) {
    for (auto &entry: modPaths) {

        std::filesystem::path configPath;
        for (const char *name: {"mod.json", "dlce.mod.json"}) {
            configPath = entry / name;
            if (std::filesystem::exists(configPath))
                break;
        }

        if (!std::filesystem::exists(configPath)) {
            // only happens if the user makes a mistake
            dbgprintf("Warn, folder has no mod config, legacy? : %s\n", entry.string().c_str());
            continue;
        }

        std::ifstream fin(configPath);
        if (!fin.is_open()) {
            std::cerr << "Failed to open " << configPath << '\n';
            continue;
        }

        json config;
        try {
            fin >> config;
        } catch (const json::parse_error &e) {
            std::cerr << "JSON parse error in " << configPath << ": " << e.what() << '\n';
            continue;
        }

        Mod mod;
        mod.dir = entry;

        // try to get name string
        if (config.contains("name") && config["name"].is_string()) {
            mod.displayName = config["name"].get<std::string>();
        } else {
            // fallback to folder name
            mod.displayName = entry.filename().string();
            std::cerr << "Warn, no 'name' in " << configPath << ", using folder name '" << mod.displayName << "'\n";
        }

        // try to get version string
        if (config.contains("version")) {
            if (config["version"].is_string()) {
                mod.version = config["version"].get<std::string>();
            } else if (config["version"].is_number()) {
                // get version string from num (ie 1 or 1.2)
                if (config["version"].is_number_integer())
                    mod.version = std::to_string(config["version"].get<long long>());
                else
                    mod.version = std::to_string(config["version"].get<double>());
            } else {
                std::cerr << "Warn, 'version' exists in " << configPath << " but has unexpected type; ignoring\n";
            }
        } else {
            // failure, default version string
            mod.version = "0.0.0.0";
        }

        // try get bool
        if (config.contains("enabled")) {
            if (config["enabled"].is_boolean()) {
                mod.enabled = config["enabled"].get<bool>();
            } else if (config["enabled"].is_number_integer()) {
                // try int
                mod.enabled = config["enabled"].get<int>() != 0;
            } else {
                std::cerr << "Warning: 'enabled' in " << configPath << " is not a bool or int; defaulting to false\n";
            }
        }

        // same logic as above
        if (config.contains("priority")) {
            if (config["priority"].is_boolean()) {
                mod.priority = config["priority"].get<bool>();
            } else if (config["priority"].is_number_integer()) {
                // try int
                mod.priority = config["priority"].get<int>() != 0;
            } else {
                std::cerr << "Warning: 'priority' in " << configPath << " is not a bool or int; defaulting to false\n";
            }
        }

        if (config.contains("items") && config["items"].is_array()) {
            const auto &items = config["items"];

            // quick pass to see if there are any paks
            bool hasPak = false;
            for (const auto &item: items) {
                if (!item.is_object())
                    continue;
                if (item.value("type", "") == "pak") {
                    hasPak = true;
                    break;
                }
            }

            if (hasPak) {
                // add mod folder, paks won't load unless the folder they are in is added also
                fs::add_source(entry.string().c_str(), FFSAddSourceFlags::SUBDIRS | FFSAddSourceFlags::APPEND | FFSAddSourceFlags::STRIP_LAST_DIR);
            }

            // pass of items to create instances
            for (const auto &item: items) {
                if (!item.is_object()) {
                    std::cerr << "Warning: item in 'items' is not an object; skipping\n";
                    continue;
                }

                std::string type = item.value("type", "");


                if (!item.contains("paths") || !item["paths"].is_array()) {
                    std::cerr << "Warning: 'paths' missing or not an array; skipping\n";
                    continue;
                }

                for (const auto &p : item["paths"]) {
                    if (!p.is_string()) {
                        std::cerr << "Warning: path is not a string; skipping\n";
                        continue;
                    }
                    std::filesystem::path path = p.get<std::string>();

                    if (path.is_relative())
                        path = entry / path;

                    if (path.is_relative())
                        path = m_Root / path;

                    if (type == "dll") {
                        // dll instance
                        auto inst = std::make_unique<DllModInstance>();
                        inst->m_dllPath = path;
                        inst->SetName(mod.displayName);
                        // push
                        mod.instances.push_back(std::move(inst));
                    } else if (type == "pak") {
                        // create pak instance
                        auto inst = std::make_unique<PakModInstance>();
                        inst->m_pakPath = path;
                        inst->SetName(mod.displayName);
                        // push
                        mod.instances.push_back(std::move(inst));
                    } else {
                        std::cerr << "Warning: " << type << " is unknown\n";
                    }
                }
            }
        }

        m_Mods.push_back(std::move(mod));
    }
}

void Loader::IndexMods() {
    if (!EnsureModsDirectoryExists())
        return;

    std::filesystem::path orderPath;
    for (const char *name: {"order.json", "dlce.order.json"}) {
        orderPath = m_Root / name;
        if (std::filesystem::exists(orderPath))
            break;
    }

    std::vector<std::filesystem::path> modPaths;

    if (std::filesystem::exists(orderPath)) {
        // open file
        std::ifstream fin(orderPath);
        if (!fin.is_open()) {
            std::cerr << "Failed to open " << orderPath << '\n';
        }

        // read JSON
        json orderJson;
        try {
            fin >> orderJson;
        } catch (const json::parse_error &e) {
            std::cerr << "JSON parse error in " << orderPath << ": " << e.what() << '\n';
        }

        // for each name in the JSON
        for (const auto &item: orderJson["order"]) {
            auto value = item.get<std::string>();
            // push path of mod folder
            modPaths.push_back(m_Root / value);
        }
    } else {

        dbgprintf("order json does not exist\n");

        // create JSON for later writing of dlce.order.json
        json j;
        j["order"] = json::array();

        for (auto &entry: std::filesystem::directory_iterator(m_Root)) {
            if (!entry.is_directory())
                continue;

            std::filesystem::path configPath;
            for (const char *name: {"mod.json", "dlce.mod.json"}) {
                configPath = entry.path() / name;
                if (std::filesystem::exists(configPath))
                    break;
            }

            if (!std::filesystem::exists(configPath)) {
                // dbgprintf("Warn, folder has no mod config, legacy? : %s\n", entry.path().string().c_str());
                continue;
            }

            // push path of mod folder
            modPaths.push_back(entry);
            j["order"].push_back(entry.path().filename());
        }

        // write auto generated order JSON with 4 space indent
        std::ofstream out(m_Root / "dlce.order.json");
        out << j.dump(2);
        out.close();
    }

    // parse mods from mod paths
    ParseMods(modPaths);
}

void Loader::LoadPhase(const ModLoadPhase phase) const {
    for (auto &mod: m_Mods) {
        if (!mod.enabled)
            continue;

        for (auto &inst: mod.instances) {
            if (inst->GetLoadPhase() == phase) {
                inst->OnLoad();
            }
        }
    }
}


void Loader::UnLoadPhase(const ModLoadPhase phase) const {
    for (auto &mod: m_Mods) {
        if (!mod.enabled)
            continue;

        for (auto &inst: mod.instances) {
            if (inst->GetLoadPhase() == phase) {
                inst->OnUnload();
            }
        }
    }
}
