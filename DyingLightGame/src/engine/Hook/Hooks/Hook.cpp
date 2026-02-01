//
// Created by Brendon on 1/25/2026.
//

#include "Hook.h"

Hook::Hook(std::string name) {
    this->name = std::move(name);
};

void Hook::enableHook() {}

safetyhook::InlineHook Hook::addHook(void *target, void *destination) {
    if (target == nullptr) {
        //IDK throw an error or smt, SYBAU
    }

    return safetyhook::create_inline(target, destination);
}