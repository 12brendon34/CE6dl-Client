//
// Created by Brendon on 1/29/2026.
//

#pragma once
#include <vector>
#include <mutex>

class IGame;

// callback type exported by mods
using mod_onpaint_t = void(*)(IGame*);

namespace ModAPI {
    // register/unregister a mod-provided OnPaint function
    void RegisterOnPaint(mod_onpaint_t cb);
    void UnregisterOnPaint(mod_onpaint_t cb);

    // called by your hook to invoke all registered callbacks
    void CallOnPaintCallbacks(IGame* pThis);
}
