//
// Created by Brendon on 1/29/2026.
//

#pragma once
#include "engine/Game/IGame.h"

//entry points type shit
extern "C" __declspec(dllexport) void OnLoad();
extern "C" __declspec(dllexport) void OnUnload();

extern "C" __declspec(dllexport) void OnPaint(IGame *pIGame); //OnPaint Hook