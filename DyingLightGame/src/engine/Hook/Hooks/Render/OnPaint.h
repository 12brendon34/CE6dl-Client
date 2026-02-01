#pragma once
#include "../Hook.h"


class IGame;

class OnPaintHook : public Hook {
public:
    OnPaintHook();
    static void hkOnPaint(IGame* pThis);
    inline static SafetyHookInline SHook;

    virtual void enableHook();
};
