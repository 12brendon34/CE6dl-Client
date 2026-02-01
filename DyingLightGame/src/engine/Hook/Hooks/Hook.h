//
// Created by Brendon on 1/25/2026.
//

#pragma once
#include <cstdint>
#include <string>
#include <safetyhook.hpp>

class Hook {
private:
    std::string name;

public:
    Hook(std::string name);
    static safetyhook::InlineHook addHook(void* target, void* destination);

    virtual ~Hook() = default;
    virtual void enableHook();
};
