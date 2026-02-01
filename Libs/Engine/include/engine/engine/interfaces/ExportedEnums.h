//
// Created by Brendon on 1/14/2026.
//
#pragma once
#include "engine/Export.h"
#include "engine/Kernel/ttl/String.h"

class ENGINE_API ELanguage {
    enum TYPE {
        Unknown = -1,
        En,
        De,
        Fr,
        Es,
        El,
        It,
        Jp,
        Pl,
        Cz,
        Ru,
        Nl,
        Br,
        Ko,
        Cn,
        Tw,
        Th,
        Tr,
        Cs,
        _COUNT
    };

public:
    TYPE FromString(ttl::string_base<char> const &);
    char const *ToString(TYPE);
};
