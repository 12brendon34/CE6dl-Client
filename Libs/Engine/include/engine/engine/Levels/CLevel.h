//
// Created by Brendon on 1/18/2026.
//

#pragma once
#include "engine/Export.h"

class ENGINE_API CLevel
{
public:
    static CRTTI m_RTTI;
    char pad_0000[88]; //0x0000
    char *m_LevelName; //0x0058
};