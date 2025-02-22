#pragma once
#include "pch.h"
#include "../TTL.h"

#ifdef _WIN32
#define DLL_EXPORT __declspec(dllimport) // For importing the function
#else
#define DLL_EXPORT
#endif

#pragma once

//most these structs are wrong, taken from old CE5 build
class FFSAddSourceFlags {
public:
    enum ENUM {
        SUBDIRS = 1,
        APPEND = 2,
        STRIP_LAST_DIR = 4,
        BROWSABLE = 8,
        ALLOW_DUPLICATES = 16,
        PRELOAD = 32
    };
};

class EFSMode {
public:
    enum TYPE {
        READ = 0,
        WRITE = 1,
        APPEND = 2,
        READ_WRITE = 3
    };
}; 

class FFSOpenFlags {
public:
    enum FLAGS {
        OPEN_CACHE = 1,
        WRITETHROUGH = 2,
        ZIP_NORMAL_COMPRESSION = 4,
        ZIP_BEST_COMPRESSION = 8,
        READ_ZIP = 16,
        CREATE = 32,
        ASYNC_BUFFERED = 64,
        ASYNC_NON_BUFFERED = 128,
        USE_CACHE_PARTITION = 256
    };
};

namespace fs {
    void add_source(class CFSSource*, enum FFSAddSourceFlags::ENUM);
    bool add_source(char const*, enum FFSAddSourceFlags::ENUM);
    void append_slash(char*, unsigned __int64);
    //bool calc_file_crc(struct fs::CrcCalcArgs&);
    void close(struct SFsFile*);
    int compare_time(__int64, __int64, unsigned int);
    bool copy(char const*, char const*, unsigned int);
    bool copy_dir(char const*, char const*, char const*, unsigned int);
    void create_backup_copy(char const*);
    //class fs::ZippedDataArchive* __ptr64 create_server_archive(char*, unsigned __int64);
    //class fs::ZippedDataArchive* __ptr64 get_server_archive(void);
    //void decompose_path(char const*, class ttl::list<class ttl::string_base<char>, class ttl::allocator>&, class ttl::string_base<char>*);
    bool does_cache_dir_exist(char const*);
    bool does_dir_exist(char const*);
    bool does_file_exist(char const*);
    void enable_read_membuffer(bool);
    bool exists(char const*);
    void extract_path(char*, unsigned int, char const*, bool);
    char const* __ptr64 file_name(struct SFsFile*);
    class ttl::string_base<char> filename_build_path(char const*, char const*, char const*, char const*);
    char* __ptr64 filename_build_path(char*, char const*, char const*, char const*, char const*);
    class ttl::string_base<char> filename_build_path_v(char const*, char const*, ...);
    char* __ptr64 filename_build_path_v(char*, unsigned int, char const*, char const*, ...);
    char* __ptr64 filename_build_path_vq(char*, unsigned int, char const*, char const*, char*);
    class ttl::string_base<char> filename_change_extension(char const*, char const*);
    char* __ptr64 filename_change_extension(char*, char const*, char const*);
    char* __ptr64 filename_change_extension_inplace(char*, char const*);
    class ttl::string_base<char> filename_change_path(char const*, char const*);
    char* __ptr64 filename_change_path(char*, char const*, char const*);
    class ttl::string_base<char> filename_get_ext(char const*);
    char* __ptr64 filename_get_ext(char*, char const*);
    class ttl::string_base<char> filename_get_fname(char const*);
    char* __ptr64 filename_get_fname(char*, char const*);
    class ttl::string_base<char> filename_get_name(char const*);
    char* __ptr64 filename_get_name(char*, char const*);
    class ttl::string_base<char> filename_get_path(char const*);
    char* __ptr64 filename_get_path(char*, char const*);
    //void find_duplicates(class ttl::list<class ttl::string_base<char>, class ttl::allocator>&, class ttl::vector<class ttl::string_base<char> > const&);
    class ttl::string_base<char> const full_path(char const*);
    class ttl::string_base<char> getOutLocationDebugHelper(void);
    char const* __ptr64 get_cache_dir(void);
    void get_file_list(class ttl::vector<class ttl::string_base<char> >&);
    //void(__cdecl* __cdecl get_search_callback(void); function pointer declaration weird thing idk
    class ttl::string_base<char> get_source_name(char const*);
    bool get_time_as_str(__int64, char*, int, char*, int);
    bool init(char const*, enum FFSAddSourceFlags::ENUM, char const*, bool, bool, char const**);
    bool init_cache(char const*);
    bool is_full_path(char const*);
    bool is_initialized(void);
    bool is_installed(char const*);
    bool is_protected(char const*);
    bool is_read_membuffer_enabled(void);
    unsigned __int64 length(struct SFsFile*);
    bool load_binary_file(void**, unsigned __int64*, char const*);
    bool load_text_file(class ttl::string_base<char>&, char const*);
    wchar_t* __ptr64 load_wide_string(char const*);
    class ttl::string_base<char> mangle_file_name(char const*, unsigned int);
    char* __ptr64 mangle_file_name(char* const, char const*, unsigned int);
    void mark_installed(char const*, bool);
    void mark_installed(bool);
    bool mkdir(char const*);
    bool mkdir_cache(char const*);
    void monitor_touch_file(char const*);
    bool native_does_dir_exist(char const*);
    bool native_does_file_exist(char const*);
    struct SFsFile* __ptr64 open(char const*, enum EFSMode::TYPE, enum FFSOpenFlags::FLAGS);
    struct SFsFile* __ptr64 open_native(class CFSSource*, char const*, enum EFSMode::TYPE, enum FFSOpenFlags::FLAGS);
    void path_normalize(char*, char const*, bool);
    void precache_file(char const*);
    void* __ptr64 read(char const*, unsigned __int64*);
    void read(void*, char const*, unsigned __int64*);
    unsigned __int64 read(struct SFsFile*, void*, unsigned __int64);
    bool read_only(char const*);
    bool read_only_remove(char const*);
    bool read_only_set(char const*);
    void refresh(char const*);
    void refresh(void);
    void rem_dir(char const*, enum FFSOpenFlags::FLAGS);
    bool rem_file(char const*, enum FFSOpenFlags::FLAGS);
    bool rem_source(class CFSSource*);
    bool rem_source(char const*);
    void remove_slash(char*);
    bool rename(char const*, char const*, unsigned int);
    class ttl::string_base<char> const root_path(char const*);
    bool same_path(char const*, char const*);
    bool save_binary_file(void const*, unsigned __int64, char const*);
    bool save_text_file(class ttl::string_base<char> const&, char const*, char const*, char const*);
    bool save_text_file(class ttl::string_base<char> const&, char const*);
    bool save_wide_string(class ttl::string_base<wchar_t> const&, char const*);
    struct FS_NAME* __ptr64 search(char const*, char const*, bool, bool);
    //class fs::idir* __ptr64 search_dir(char const*);
    struct FS_NAME* __ptr64 search_substring(char const*);
    //bool seek(struct SFsFile*, __int64, enum EFSSeek::TYPE);
    bool set_eof(struct SFsFile*);
    //struct fs::IFsMonitor* __ptr64 set_monitor(struct fs::IFsMonitor*);
    //void set_search_callback(void(__cdecl*);
    bool set_write_time(char const*, __int64);
    void shutdown(void);
    bool source_exists(char const*);
    unsigned __int64 tell(struct SFsFile*);
    char const* __ptr64 unmangle_file_name(char const*, class ttl::string_base<char>&, unsigned int&);
    char const* __ptr64 unmangle_file_name(char const*, char* const, unsigned int&);
    unsigned int unmangle_file_name_flagsonly(char const*, unsigned int);
    class ttl::string_base<char> unmangle_file_name_nameonly(char const*);
    unsigned __int64 write(struct SFsFile*, void const*, unsigned __int64);
    char const* __ptr64 write_path(void);
    __int64 write_time(char const*);
};

extern "C" DLL_EXPORT bool Main(void);
bool CrashCanShowMessageBox(void);
void CrashClose(void);
void CrashShowCallstackInAsserts(bool);
void CrashShowMessageBox(bool);