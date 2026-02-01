//
// Created by Brendon on 1/13/2026.
//

#pragma once
#include "engine/Export.h"

namespace Log {
    class ELevel {
    public:
        enum TYPE {};
    };

    class ENGINE_API Settings {
    public:
        Settings();
        Settings &operator=(Settings &&);
        Settings &operator=(Settings const &);
        ELevel::TYPE GetCategoryLevel(char const *) const;
        ELevel::TYPE GetLevel() const;
        static Settings &Instance();
        bool IsMessageSource() const;
        void SetCategoryLevel(char const *, ELevel::TYPE);
        void SetLevel(ELevel::TYPE);
        void SetMessageSource(bool);
    };
}
