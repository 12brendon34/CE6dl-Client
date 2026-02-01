#include "OnPaint.h"
#include "engine/ModAPI.h"
#include <Windows.h>

OnPaintHook::OnPaintHook() : Hook("OnPaintHook") {}

void OnPaintHook::enableHook() {
    //this shit so fucking gay, especially since the engine dll is linked
    auto hEngine = GetModuleHandle("engine_x64_rwdi.dll");
    auto hkaddress = GetProcAddress(hEngine, "?OnPaint@IGame@@QEAAXXZ");

    SHook = addHook(reinterpret_cast<void *>(hkaddress), reinterpret_cast<void *>(hkOnPaint));
}

void OnPaintHook::hkOnPaint(IGame *pThis) {
    ModAPI::CallOnPaintCallbacks(pThis);

    return SHook.call(pThis);
}
