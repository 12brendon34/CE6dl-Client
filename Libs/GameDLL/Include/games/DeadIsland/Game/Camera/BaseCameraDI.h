//
// Created by Brendon on 1/18/2026.
//

#pragma once
#include "engine/Cameras/IBaseCamera.h"

class BaseCameraDI : IBaseCamera {
    /*
    a1->qword50 = 0;
    a1->qword0 = &BaseCameraDI::`vftable';
    a1->qword10 = &BaseCameraDI::`vftable';
    a1->qword18 = &BaseCameraDI::`vftable';
    a1->qword20 = &BaseCameraDI::`vftable';
    a1->qword40 = &BaseCameraDI::`vftable';
    a1->m_IsActive = 0;
    return a1;
    */
    public:
    char _pad[0x9];
    bool m_IsActive;
};
static_assert(sizeof(BaseCameraDI) == 0x60u);