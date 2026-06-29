//
// Created by Brendon on 1/29/2026.
//

#pragma once
#include <vector>
#include <mutex>

class IGame;

// callback type exported by mods
using mod_onpaint_t = void(*)(IGame*);
using mod_onkey_t = void(*)(int, bool);
using mod_on_imgui_t = void(*)(void* context);

namespace ModAPI {
    // register/unregister a mod-provided OnPaint function
    void RegisterOnPaint(mod_onpaint_t cb);
    void UnregisterOnPaint(mod_onpaint_t cb);

    void RegisterOnKey(mod_onkey_t cb);
    void UnregisterOnKey(mod_onkey_t cb);

    // called by your hook to invoke all registered callbacks
    void CallOnPaintCallbacks(IGame* pThis);
    void CallOnKeyCallbacks(int key, bool isDown);

    void RegisterOnImGui(mod_on_imgui_t cb);
    void UnregisterOnImGui(mod_on_imgui_t cb);
    void CallOnImGuiCallbacks();
    void SetImGuiContext(void* ctx);

    void SetMenuKey(int vkey);
    int GetMenuKey();
    void ToggleMenu();
    bool IsMenuOpen();
    void SetMenuOpen(bool open);
}
