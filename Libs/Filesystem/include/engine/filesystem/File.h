//
// Created by Brendon on 1/13/2026.
//
#pragma once
#include "Filesystem.h"
#include "engine/Export.h"
#include "engine/Kernel/ttl/String.h"

class EFSSeek {
public:
    enum TYPE {};
};

namespace fs {
    class ENGINE_API file {
    public:
        file(SFsFile *);
        file();
        bool is_handle_valid() const;

        virtual ~file();
        virtual bool open(char const *path, EFSMode::TYPE, FFSOpenFlags::FLAGS);
        virtual void close();
        virtual unsigned __int64 length();
        virtual unsigned __int64 tell();
        virtual bool seek(__int64, EFSSeek::TYPE);
        virtual unsigned __int64 read(void *, unsigned __int64);
        virtual unsigned __int64 write(void const *, unsigned __int64);
        virtual bool eof();
        virtual void set_eof();
        virtual char const *name() const;
        virtual bool open_from_handle(SFsFile *);
    };

    class ENGINE_API ifile : public file {
    public:
        ifile(ifile const &);
        ifile();
        ifile &operator=(ifile const &);
        ifile &operator>>(ttl::string_base<char> &);
        ifile &operator>>(ttl::string_base<wchar_t> &);

        // ifile& operator>>(ttl::tstring_base<char> &);
        // ifile& operator>>(ttl::tstring_base<wchar_t> &);
        // ifile& operator>>(ttl::vector<ttl::string_base<char> > &);
        ifile &operator>>(bool &);
        ifile &operator>>(char *);
        ifile &operator>>(char **);
        ifile &operator>>(wchar_t **);
        ifile &operator>>(char const **);
        ifile &operator>>(wchar_t const **);
        ifile &operator>>(wchar_t *);
        ifile &operator<<(ttl::string_base<char> &);
        ifile &operator<<(ttl::string_base<wchar_t> &);

        // ifile& operator<<(ttl::tstring_base<char> &);
        // ifile& operator<<(ttl::tstring_base<wchar_t> &);
        ifile &operator<<(ttl::string_base<char> const &);
        ifile &operator<<(ttl::string_base<wchar_t> const &);

        // ifile& operator<<(ttl::tstring_base<char> const &);
        // ifile& operator<<(ttl::tstring_base<wchar_t> const &);
        // ifile& operator<<(ttl::vector<ttl::string_base<char> > const &);
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

        // vtable override, lucky me so order don't really matter
        ~ifile() override;
        bool eof() override;
    };
} // namespace fs
