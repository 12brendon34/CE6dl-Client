//
// Created by Brendon on 1/13/2026.
//
#pragma once
#include "engine/Export.h"

class ENGINE_API vec2 {
public:
    float x, y;
};

struct ENGINE_API vec3 {
    float x, y, z;
};

struct ENGINE_API vec4 {
    float x, y, z, w;
};

struct ENGINE_API alignas(16) vec4a {
    float x, y, z, w;
};

struct ENGINE_API quat {
    float x, y, z, w;
};

struct aabb {
    vec3 origin;
    vec3 span;
};

struct extents {
    vec3 min;
    vec3 max;
};
