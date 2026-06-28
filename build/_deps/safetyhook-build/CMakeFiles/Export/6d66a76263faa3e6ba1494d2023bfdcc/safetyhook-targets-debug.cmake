#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "safetyhook::safetyhook" for configuration "Debug"
set_property(TARGET safetyhook::safetyhook APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(safetyhook::safetyhook PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/safetyhook.lib"
  )

list(APPEND _cmake_import_check_targets safetyhook::safetyhook )
list(APPEND _cmake_import_check_files_for_safetyhook::safetyhook "${_IMPORT_PREFIX}/lib/safetyhook.lib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
