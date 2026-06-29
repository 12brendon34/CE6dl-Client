//
// Created by Brendon on 1/25/2026.
//

#include "HookManager.h"
#include "Hooks/Render/D3D11Hook.h"
#include "Hooks/Render/OnPaint.h"
#include "engine/Debug.h"

std::vector<std::shared_ptr<Hook>> HookManager::hooks;

void HookManager::initHooks() {
    if (!D3D11Hook::Initialize()) {
        dbgprintf("D3D11Hook::Initialize() failed.\n");
        return;
    }
    addHook<OnPaintHook>();

    for (const auto &hook: hooks)
        hook->enableHook();
}

void HookManager::uninitHooks() {
    D3D11Hook::Shutdown();
    hooks.clear();
}
