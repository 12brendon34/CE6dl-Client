//
// Created by Brendon on 1/13/2026.
//

#pragma once
#include "engine/Export.h"
#include "engine/Kernel/ttl/String.h"

class ENGINE_API MiniZ {
public:
    bool ZipAddData(void *, char const *, void const *, unsigned int);
    void ZipClose(void *);
    void *ZipCreate(char const *);
};

namespace MiniZ {
    class ENGINE_API Archive {
    public:
        Archive(char const *);
        Archive(void);
        ~Archive();

        Archive &operator=(Archive const &);
        bool AddData(char const *, ttl::string_base<char> const &);
        bool AddData(char const *, void const *, unsigned int);
        bool Create(char const *);
    };
} // namespace MiniZ
