//
// Created by Brendon on 1/25/2026.
//

#pragma once
#include <memory>
#include <vector>

#include "Hooks/Hook.h"

class HookManager {
public:
    static std::vector<std::shared_ptr<Hook> > hooks;

    template<typename T, typename... ArgsT>
    static void addHook(ArgsT &&... args) {
        auto hookPtr = std::make_shared<T>(std::forward<ArgsT>(args)...);
        hooks.emplace_back(std::move(hookPtr));
    }

    static void initHooks();
    static void uninitHooks();
};
