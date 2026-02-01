//
// Created by Brendon on 1/25/2026.
//

#include "HookManager.h"
#include "Hooks/Render/OnPaint.h"

std::vector<std::shared_ptr<Hook> > HookManager::hooks;

void HookManager::initHooks() {
    addHook<OnPaintHook>();

    for (const auto &hook: hooks)
        hook->enableHook();
}

void HookManager::uninitHooks() {
    hooks.clear();
}
