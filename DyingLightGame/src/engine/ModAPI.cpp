//
// Created by Brendon on 1/29/2026.
//

#include "ModAPI.h"
#include <algorithm>
#include <iostream>
#include "engine/Game/IGame.h"

namespace {
    std::vector<mod_onpaint_t> g_onpaint_callbacks;
    std::mutex g_onpaint_mutex;

    std::vector<mod_onkey_t> g_onkey_callbacks;
    std::mutex g_onkey_mutex;

    std::vector<mod_on_imgui_t> g_on_imgui_callbacks;
    std::mutex g_on_imgui_mutex;
    void* g_imgui_context = nullptr;
}

void ModAPI::RegisterOnPaint(mod_onpaint_t cb) {
    if (!cb) return;
    std::lock_guard lock(g_onpaint_mutex);
    // avoid duplicates
    if (std::ranges::find(g_onpaint_callbacks, cb) == g_onpaint_callbacks.end())
        g_onpaint_callbacks.push_back(cb);
}

void ModAPI::UnregisterOnPaint(const mod_onpaint_t cb) {
    std::lock_guard lock(g_onpaint_mutex);
    auto it = std::ranges::remove(g_onpaint_callbacks, cb).begin();
    if (it != g_onpaint_callbacks.end()) g_onpaint_callbacks.erase(it, g_onpaint_callbacks.end());
}

void ModAPI::CallOnPaintCallbacks(IGame* pThis) {
    std::vector<mod_onpaint_t> copy;
    {
        std::lock_guard lock(g_onpaint_mutex);
        copy = g_onpaint_callbacks;
    }

    for (const auto cb : copy) {
        try {
            if (cb) cb(pThis);
        } catch (...) {
            std::cerr << "Exception in mod OnPaint callback\n";
        }
    }
}

void ModAPI::RegisterOnKey(mod_onkey_t cb) {
    if (!cb) return;
    std::lock_guard lock(g_onkey_mutex);
    if (std::ranges::find(g_onkey_callbacks, cb) == g_onkey_callbacks.end())
        g_onkey_callbacks.push_back(cb);
}

void ModAPI::UnregisterOnKey(const mod_onkey_t cb) {
    std::lock_guard lock(g_onkey_mutex);
    auto it = std::ranges::remove(g_onkey_callbacks, cb).begin();
    if (it != g_onkey_callbacks.end()) g_onkey_callbacks.erase(it, g_onkey_callbacks.end());
}

void ModAPI::CallOnKeyCallbacks(int key, bool isDown) {
    std::vector<mod_onkey_t> copy;
    {
        std::lock_guard lock(g_onkey_mutex);
        copy = g_onkey_callbacks;
    }

    for (const auto cb : copy) {
        try {
            if (cb) cb(key, isDown);
        } catch (...) {
            std::cerr << "exception in mod onkey callback\n";
        }
    }
}

void ModAPI::RegisterOnImGui(mod_on_imgui_t cb) {
    if (!cb) return;
    std::lock_guard lock(g_on_imgui_mutex);
    if (std::ranges::find(g_on_imgui_callbacks, cb) == g_on_imgui_callbacks.end())
        g_on_imgui_callbacks.push_back(cb);
}

void ModAPI::UnregisterOnImGui(const mod_on_imgui_t cb) {
    std::lock_guard lock(g_on_imgui_mutex);
    auto it = std::ranges::remove(g_on_imgui_callbacks, cb).begin();
    if (it != g_on_imgui_callbacks.end()) g_on_imgui_callbacks.erase(it, g_on_imgui_callbacks.end());
}

void ModAPI::CallOnImGuiCallbacks() {
    std::vector<mod_on_imgui_t> copy;
    void* ctx = nullptr;
    {
        std::lock_guard lock(g_on_imgui_mutex);
        copy = g_on_imgui_callbacks;
        ctx = g_imgui_context;
    }

    for (const auto cb : copy) {
        try {
            if (cb) cb(ctx);
        } catch (...) {
            std::cerr << "exception in mod onimgui callback\n";
        }
    }
}

void ModAPI::SetImGuiContext(void* ctx) {
    std::lock_guard lock(g_on_imgui_mutex);
    g_imgui_context = ctx;
}

#include <atomic>

namespace {
    int g_MenuKey = 0x2D; // VK_INSERT default
    std::atomic<bool> g_MenuOpen = false;
    std::mutex g_MenuMutex; // Only used for g_MenuKey now
}

void ModAPI::SetMenuKey(int vkey) {
    std::lock_guard lock(g_MenuMutex);
    g_MenuKey = vkey;
}

int ModAPI::GetMenuKey() {
    std::lock_guard lock(g_MenuMutex);
    return g_MenuKey;
}

void ModAPI::ToggleMenu() {
    bool current = g_MenuOpen.load();
    g_MenuOpen.store(!current);
    if (!current) ClipCursor(nullptr); // Only clip when opening
}

bool ModAPI::IsMenuOpen() {
    return g_MenuOpen.load();
}

void ModAPI::SetMenuOpen(bool open) {
    g_MenuOpen.store(open);
    if (open) ClipCursor(nullptr);
}
