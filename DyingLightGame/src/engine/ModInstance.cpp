//
// Created by Brendon on 1/29/2026.
//

#include "ModInstance.h"
#include "engine/Debug.h"
#include "engine/filesystem/Filesystem.h"
#include <iostream>

#include "ModAPI.h"

[[nodiscard]] ModLoadPhase DllModInstance::GetLoadPhase() const {
    return ModLoadPhase::DllPhase;
}

bool DllModInstance::OnLoad() {
    m_dllPath = std::filesystem::absolute(m_dllPath);
    m_hMod = LoadLibraryExW(m_dllPath.c_str(), nullptr, LOAD_WITH_ALTERED_SEARCH_PATH);
    if (!m_hMod) {
        dbgprintf("LoadLibraryEx failed for : %ls", m_dllPath.c_str());
        return false;
    }

    onLoad_ = reinterpret_cast<on_load_t>(GetProcAddress(m_hMod, "OnLoad"));
    onUnload_ = reinterpret_cast<on_unload_t>(GetProcAddress(m_hMod, "OnUnload"));
    onPaint_ = reinterpret_cast<on_paint_t>(GetProcAddress(m_hMod, "OnPaint"));

    if (onLoad_) {
        try {
            if (!onLoad_()) {
                std::cerr << "Mod_OnLoad returned false for " << GetName() << "\n";
                if (onPaint_)
                    ModAPI::UnregisterOnPaint(onPaint_);
                return false;
            }
        } catch (...) {
            std::cerr << "Exception calling OnLoad for " << GetName() << "\n";
            if (onPaint_)
                ModAPI::UnregisterOnPaint(onPaint_);
            return false;
        }
    }

    if (onPaint_)
        ModAPI::RegisterOnPaint(onPaint_);
    return true;
}

void DllModInstance::OnUnload() {
    try {
        if (onUnload_)
            onUnload_();
    } catch (...) {
        std::cerr << "Exception calling OnUnload for " << GetName() << "\n";
    }

    if (onPaint_) {
        ModAPI::UnregisterOnPaint(onPaint_);
        onPaint_ = nullptr;
    }

    if (m_hMod) {
        FreeLibrary(m_hMod);
        m_hMod = nullptr;
    }
}


ModLoadPhase PakModInstance::GetLoadPhase() const {
    return ModLoadPhase::PakPhase;
}

bool PakModInstance::OnLoad() {
    if (m_pakPath.empty()) {
        std::cerr << "PakModInstance has empty path for " << GetName() << '\n';
        return false;
    }

    try {
        if (!std::filesystem::exists(m_pakPath)) {
            std::cerr << "Pak file not found: " << m_pakPath << " (mod: " << GetName() << ")\n";
            return false;
        }

        m_pakPath = std::filesystem::absolute(m_pakPath);
        m_pakPathNarrow = m_pakPath.string();
    } catch (const std::filesystem::filesystem_error &e) {
        std::cerr << "Filesystem error for " << m_pakPath << " (mod: " << GetName() << "): " << e.what() << '\n';
        return false;
    } catch (const std::exception &e) {
        std::cerr << "Error preparing pak path " << m_pakPath << " (mod: " << GetName() << "): " << e.what() << '\n';
        return false;
    }

    if (!fs::add_source(m_pakPathNarrow.c_str(), FFSAddSourceFlags::SUBDIRS)) {
        std::cerr << "Failed to mount pak: " << m_pakPathNarrow << " (mod: " << GetName() << ")\n";
        m_pakPathNarrow.clear();
        m_mounted = false;
        return false;
    }

    m_mounted = true;

    return true;
}

void PakModInstance::OnUnload() {
    if (!m_mounted)
        return;

    try {
        fs::rem_source(m_pakPathNarrow.c_str());
    } catch (const std::exception &e) {
        std::cerr << "Exception unmounting pak: " << m_pakPathNarrow << " (mod: " << GetName() << "): " << e.what() << "\n";
    } catch (...) {
        std::cerr << "Unknown exception unmounting pak: " << m_pakPathNarrow << " (mod: " << GetName() << ")\n";
    }

    m_mounted = false;
    m_pakPathNarrow.clear();
}
