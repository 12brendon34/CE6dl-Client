cmake_minimum_required(VERSION 3.20)
project(ExampleMod LANGUAGES CXX)
set(CMAKE_VERBOSE_MAKEFILE ON)

add_library(ExampleMod SHARED
        src/library.cpp
        src/library.h)

CPMAddPackage(NAME imgui GITHUB_REPOSITORY ocornut/imgui VERSION 1.90.4)

if (imgui_ADDED OR imgui_SOURCE_DIR)
    target_sources(ExampleMod PRIVATE
            ${imgui_SOURCE_DIR}/imgui.cpp
            ${imgui_SOURCE_DIR}/imgui_draw.cpp
            ${imgui_SOURCE_DIR}/imgui_tables.cpp
            ${imgui_SOURCE_DIR}/imgui_widgets.cpp
    )
    target_include_directories(ExampleMod PRIVATE
            ${imgui_SOURCE_DIR}
    )
endif()

target_compile_features(ExampleMod PUBLIC cxx_std_20)
target_include_directories(ExampleMod
        PRIVATE
        ${CMAKE_SOURCE_DIR}/libs/Engine/include
        ${CMAKE_SOURCE_DIR}/libs/Filesystem/include
        ${CMAKE_SOURCE_DIR}/libs/GameDLL/include
        src
)

target_link_libraries(ExampleMod
        PRIVATE
        ChromeEngine::Engine
        ChromeEngine::GameDLL
        ChromeEngine::Filesystem
        #Steam::API
        libhat::libhat
)