#pragma once
#include <polyhook2/Detour/x64Detour.hpp>

class Hook {
public:
    virtual void install() = 0;
    virtual ~Hook() = default;
};

class HookManager {
public:
    static HookManager& get() {
        static HookManager instance;
        return instance;
    }

    void add(std::unique_ptr<Hook> hook) {
        hook->install();
        hooks.push_back(std::move(hook));
    }

private:
    std::vector<std::unique_ptr<Hook>> hooks;
};
