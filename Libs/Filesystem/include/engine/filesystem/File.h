//
// Created by Brendon on 1/13/2026.
//
#pragma once
#include "engine/Export.h"
#include "engine/Kernel/ttl/String.h"

namespace fs {
    class ENGINE_API ifile {
    public:
        ifile(ifile const &);
        ifile();
        ifile &operator=(ifile const &);
        ifile &operator>>(ttl::string_base<char> &);
        ifile &operator>>(ttl::string_base<wchar_t> &);

        //ifile& operator>>(ttl::tstring_base<char> &);
        //ifile& operator>>(ttl::tstring_base<wchar_t> &);
        //ifile& operator>>(ttl::vector<ttl::string_base<char> > &);
        ifile &operator>>(bool &);
        ifile &operator>>(char *);
        ifile &operator>>(char * *);
        ifile &operator>>(wchar_t * *);
        ifile &operator>>(char const * *);
        ifile &operator>>(wchar_t const * *);
        ifile &operator>>(wchar_t *);
        ifile &operator<<(ttl::string_base<char> &);
        ifile &operator<<(ttl::string_base<wchar_t> &);

        //ifile& operator<<(ttl::tstring_base<char> &);
        //ifile& operator<<(ttl::tstring_base<wchar_t> &);
        ifile &operator<<(ttl::string_base<char> const &);
        ifile &operator<<(ttl::string_base<wchar_t> const &);

        //ifile& operator<<(ttl::tstring_base<char> const &);
        //ifile& operator<<(ttl::tstring_base<wchar_t> const &);
        //ifile& operator<<(ttl::vector<ttl::string_base<char> > const &);
        ifile &operator<<(char *);
        ifile &operator<<(wchar_t *);
        ifile &operator<<(char const *);
        ifile &operator<<(wchar_t const *);
        ifile &operator<<(bool);

        bool get_bool();
        float get_float();
        int get_int();
        unsigned int get_uint();
        int printf(ttl::string_base<char> const &);
        int printf(char const *, ...);
        void put_bool(bool);
        void put_float(float);
        void put_int(int);
        void put_uint(unsigned int);
        ~ifile();

        //virtual bool eof();
    };
}
