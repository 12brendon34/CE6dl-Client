//
// Created by Brendon on 1/12/2026.
//

#pragma once
#include <cstdint>
#include "engine/Kernel/ttl/String.h"

struct SFsFile {};

class CFSSource {};

class FFSAddSourceFlags {
public:
    enum ENUM {
        SUBDIRS = 1,
        APPEND = 2,
        STRIP_LAST_DIR = 4,
        BROWSABLE = 8,
        ALLOW_DUPLICATES = 16,
        PRELOAD = 32,
        DISABLE_CACHE_INIT = 64 //guessed name
    };

    friend constexpr ENUM operator|(const ENUM a, const ENUM b) {
        using UT = std::underlying_type_t<ENUM>;
        return static_cast<ENUM>(static_cast<UT>(a) | static_cast<UT>(b));
    }

    friend constexpr ENUM operator&(const ENUM a, const ENUM b) {
        using UT = std::underlying_type_t<ENUM>;
        return static_cast<ENUM>(static_cast<UT>(a) & static_cast<UT>(b));
    }

    friend ENUM &operator|=(ENUM &a, const ENUM b) {
        a = a | b;
        return a;
    }

    friend ENUM &operator&=(ENUM &a, const ENUM b) {
        a = a & b;
        return a;
    }
};

class FFSOpenFlags {
public:
    enum FLAGS {};
};

class EFSMode {
public:
    enum TYPE {};
};

namespace fs {
    class ZippedDataArchive {};

    struct CrcCalcArgs {};

    // Add / query sources
    void add_source(CFSSource *source, FFSAddSourceFlags::ENUM flag);
    bool add_source(char const *source, FFSAddSourceFlags::ENUM flag);
    bool init(char const *, FFSAddSourceFlags::ENUM, char const *, bool, bool, char const **);
    bool init_cache(char const *);
    bool is_initialized();
    void append_slash(char *path, uint64_t buffer_size);
    void remove_slash(char *);
    void path_normalize(char *, char const *, bool);
    bool is_full_path(char const *);
    char const *file_name(SFsFile *);
    bool same_path(char const *, char const *);
    void extract_path(char *, unsigned int, char const *, bool);
    char *filename_build_path(char *, char const *, char const *, char const *, char const *);
    char *filename_build_path_v(char *, unsigned int, char const *, char const *, ...);
    char *filename_build_path_vq(char *, unsigned int, char const *, char const *, char *);
    char *filename_change_extension(char *, char const *, char const *);
    char *filename_change_extension_inplace(char *, char const *);
    char *filename_change_path(char *, char const *, char const *);
    char *filename_get_ext(char *, char const *);
    char *filename_get_fname(char *, char const *);
    char *filename_get_name(char *, char const *);
    char *filename_get_path(char *, char const *);
    char *mangle_file_name(char *, char const *, unsigned int);
    char const *unmangle_file_name(char const *, char *, unsigned int &);
    char const *unmangle_file_name(char const *, ttl::string_base<char> &, unsigned int &);
    unsigned int unmangle_file_name_flagsonly(char const *, unsigned int);
    ttl::string_base<char> filename_build_path(char const *, char const *, char const *, char const *);
    ttl::string_base<char> filename_build_path_v(char const *, char const *, ...);
    ttl::string_base<char> filename_change_extension(char const *, char const *);
    ttl::string_base<char> filename_change_path(char const *, char const *);
    ttl::string_base<char> filename_get_ext(char const *);
    ttl::string_base<char> filename_get_fname(char const *);
    ttl::string_base<char> filename_get_name(char const *);
    ttl::string_base<char> filename_get_path(char const *);
    ttl::string_base<char> const full_path(char const *);
    ttl::string_base<char> getOutLocationDebugHelper();
    ttl::string_base<char> get_source_name(char const *);
    ttl::string_base<char> mangle_file_name(char const *, unsigned int);
    ttl::string_base<char> unmangle_file_name_nameonly(char const *);
    ttl::string_base<char> const root_path(char const *);
    bool calc_file_crc(CrcCalcArgs &crc_args);
    bool does_cache_dir_exist(char const *);
    bool does_dir_exist(char const *);
    bool does_file_exist(char const *);
    bool exists(char const *);
    bool source_exists(char const *);
    bool is_installed(char const *);
    void mark_installed(char const *, bool);
    void mark_installed(bool);
    bool is_protected(char const *);
    bool is_read_membuffer_enabled();
    void enable_read_membuffer(bool);
    bool copy(char *source_path, char *dest_path, unsigned int buffer_size);
    bool copy_dir(char *source_path, char *dest_path, char *, unsigned int buffer_size);
    bool rename(char const *, char const *, unsigned int);
    bool rem_file(char const *, FFSOpenFlags::FLAGS);
    void rem_dir(char const *, FFSOpenFlags::FLAGS);
    bool rem_source(CFSSource *);
    bool rem_source(char const *);
    bool mkdir(char const *);
    bool mkdir_cache(char const *);
    bool native_does_dir_exist(char const *);
    bool native_does_file_exist(char const *);
    void monitor_touch_file(char const *);
    void create_backup_copy(char const *);
    ZippedDataArchive *create_server_archive(char *, unsigned long long);
    ZippedDataArchive *get_server_archive();
    SFsFile *open(char const *, EFSMode::TYPE, FFSOpenFlags::FLAGS);
    SFsFile *open_native(CFSSource *, char const *, EFSMode::TYPE, FFSOpenFlags::FLAGS);
    void close(SFsFile *);
    unsigned tell(SFsFile *);
    unsigned length(SFsFile *);
    bool set_eof(SFsFile *);
    bool set_write_time(char const *, long long);
    uint64_t write_time(char const *);
    void *read(char const *, unsigned long long *);
    void read(void *, char const *, unsigned long long);
    unsigned read(SFsFile *, void *, unsigned long long);
    unsigned write(SFsFile *, void const *, unsigned long long);
    bool save_binary_file(void const *, unsigned long long, char const *);
    bool load_binary_file(void **, unsigned long long *, char const *);
    bool save_text_file(ttl::string_base<char> const &, char const *, char const *, char const *);
    bool save_text_file(ttl::string_base<char> const &, char const *);
    bool save_wide_string(ttl::string_base<wchar_t> const &, char const *);
    bool load_text_file(ttl::string_base<char> &, char const *);
    wchar_t *load_wide_string(char const *);
    bool read_only(char const *);
    bool read_only_set(char const *);
    bool read_only_remove(char const *);
    void precache_file(char const *);
    void refresh();
    void refresh(char const *);
    void shutdown();
    char const *write_path();
    char const *get_cache_dir();
    int compare_time(uint64_t time1, uint64_t time2, unsigned int tolerance_ms);
    bool get_time_as_str(long long, char *, int, char *, int);

    //unimp
    //void decompose_path(char const*, ttl::list<ttl::string_base<char>, ttl::allocator>&, ttl::string_base<char>*);
    //void find_duplicates(ttl::list<ttl::string_base<char>, ttl::allocator>&, ttl::vector<ttl::string_base<char>> const&);
    //void get_file_list(ttl::vector<ttl::string_base<char>>&);
    //void(__cdecl* __cdecl get_search_callback();
    //FS_NAME* search(char const*, char const*, bool, bool);
    //fs::idir* search_dir(char const*);
    //FS_NAME* search_substring(char const*);
    //bool seek(SFsFile*, long long, EFSSeek::TYPE);
    //fs::IFsMonitor* set_monitor(fs::IFsMonitor*);
    //void set_search_callback(void(__cdecl*);
};
