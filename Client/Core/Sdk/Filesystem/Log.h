#pragma once

namespace Log {

    class ELevel {
    public:
        enum TYPE;
    };

    class Settings {
    public:
        static class Log::Settings& Instance(void);

        __cdecl Settings(void);
        enum Log::ELevel::TYPE GetCategoryLevel(char const*) const;
        enum Log::ELevel::TYPE GetLevel(void) const;
        bool IsMessageSource(void) const;
        void SetCategoryLevel(char const*, enum Log::ELevel::TYPE);
        void SetLevel(enum Log::ELevel::TYPE);
        void SetMessageSource(bool);
    };
};