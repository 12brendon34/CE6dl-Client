//
// Created by Brendon on 1/29/2026.
//

#include "ModAPI.h"
#include <algorithm>
#include <iostream>

namespace {
    std::vector<mod_onpaint_t> g_onpaint_callbacks;
    std::mutex g_onpaint_mutex;
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
