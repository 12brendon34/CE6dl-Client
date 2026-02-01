add_library(ChromeEngine::Filesystem SHARED IMPORTED GLOBAL
        include/engine/filesystem/File.h
        include/engine/filesystem/Miniz.h
        include/engine/filesystem/LogSettings.h)

set_target_properties(ChromeEngine::Filesystem PROPERTIES
        IMPORTED_IMPLIB "${CMAKE_CURRENT_LIST_DIR}/filesystem_x64_rwdi.lib"
        IMPORTED_LOCATION "${CMAKE_CURRENT_LIST_DIR}/filesystem_x64_rwdi.dll"
)

target_include_directories(ChromeEngine::Filesystem INTERFACE
        include
)
