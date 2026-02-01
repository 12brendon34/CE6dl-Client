//
// Created by Brendon on 1/13/2026.
//
#pragma once
#include <cstdlib>
#include <cstring>

namespace ttl {
    template<typename CharT>
    class string_base {
        CharT *m_Buffer;
        unsigned int m_Size;
        unsigned int m_Capacity;

    public:
        CharT *c_str() {
            CharT *result = m_Buffer;
            if (!result)
                return nullptr;
            return result;
        }

        string_base(CharT *str, const unsigned int count = UINT_MAX) {
            unsigned int i = 0;
            //stop early on term
            for (; i < count; ++i) {
                if (!str[i])
                    break;
            }

            this->m_Capacity = i; //number of characters (no term)
            this->m_Size = i;

            if (i) {
                // i chars + 1 (null term)
                auto buf = static_cast<char *>(std::malloc(i + 1));
                this->m_Buffer = buf;

                std::memcpy(buf, str, static_cast<size_t>(this->m_Size));
                buf[this->m_Size] = '\0';
            } else {
                this->m_Buffer = nullptr;
            }
        }

        string_base(const string_base &src) {
            unsigned int mSize = src.m_Size;
            if (mSize) {
                auto buf = static_cast<char *>(std::malloc(mSize + 1));
                this->m_Buffer = buf;
                this->m_Size = mSize;
                this->m_Capacity = mSize;

                std::memcpy(buf, src.m_Buffer, static_cast<size_t>(this->m_Size + 1));
            } else {
                this->m_Buffer = nullptr;
                this->m_Capacity = 0;
                this->m_Size = 0;
            }
        }
    };
};
