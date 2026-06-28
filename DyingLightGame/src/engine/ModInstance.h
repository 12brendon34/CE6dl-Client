//
// Created by Brendon on 1/29/2026.
//

#pragma once
#include <filesystem>
#include <windows.h>

class IGame;

enum class ModLoadPhase {
    DllPhase,
    PakPhase,
};

class ModInstance {
public:
    ModInstance() = default;

    virtual ~ModInstance() = default;
    virtual bool OnLoad() = 0;
    virtual void OnUnload() = 0;

    [[nodiscard]] virtual ModLoadPhase GetLoadPhase() const = 0;

    [[nodiscard]] const char *GetName() const {
        return m_name.c_str();
    }

    void SetName(std::string_view n) { m_name.assign(n); }

protected:
    std::string m_name; //shares name of parent mod
};

class DllModInstance : public ModInstance {
public:
    using on_load_t = bool(*)();
    using on_unload_t = void(*)();
    using on_paint_t = void(*)(IGame*);
    using on_key_t = void(*)(int, bool);
    using on_imgui_t = void(*)(void*);

    HMODULE m_hMod = nullptr;
    std::filesystem::path m_dllPath;

    on_load_t onLoad_ = nullptr;
    on_unload_t onUnload_ = nullptr;
    on_paint_t onPaint_ = nullptr;
    on_key_t onKey_ = nullptr;
    on_imgui_t onImGui_ = nullptr;

    [[nodiscard]] virtual ModLoadPhase GetLoadPhase() const;

    virtual bool OnLoad();
    virtual void OnUnload();
};

class PakModInstance : public ModInstance {
public:
    std::filesystem::path m_pakPath;
    std::string m_pakPathNarrow;
    bool m_mounted = false;

    [[nodiscard]] virtual ModLoadPhase GetLoadPhase() const;

    virtual bool OnLoad();
    virtual void OnUnload();
};

struct Mod {
    std::string displayName{};
    std::string version{};
    std::filesystem::path dir{};
    bool enabled = false;
    bool priority = false;
    std::vector<std::unique_ptr<ModInstance> > instances;
};
