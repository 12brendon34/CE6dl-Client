cmake_minimum_required(VERSION 3.20)
project(DyingLightGame LANGUAGES CXX)
set(CMAKE_VERBOSE_MAKEFILE ON)

include(${CMAKE_SOURCE_DIR}/cmake/CPM.cmake)

if (STEAM_PLATFORM)
    add_definitions(-DSTEAM_PLATFORM=1)
endif (STEAM_PLATFORM)

add_executable(DyingLightGame WIN32
        resources/Resource.rc
        src/engine/Game/WinFrame.cpp
        src/engine/engine/CustomSplash.cpp
        src/engine/engine/CustomSplash.h
        src/engine/Hook/HookManager.cpp
        src/engine/Hook/HookManager.h
        src/engine/Hook/Hooks/Hook.cpp
        src/engine/Hook/Hooks/Hook.h
        src/engine/Hook/Hooks/Render/OnPaint.cpp
        src/engine/Hook/Hooks/Render/OnPaint.h
        src/engine/Hook/Hooks/Render/D3D11Hook.cpp
        src/engine/Hook/Hooks/Render/D3D11Hook.h
        src/engine/ModLoader.cpp
        src/engine/ModLoader.h
        src/engine/ModInstance.cpp
        src/engine/ModInstance.h
        src/engine/ModAPI.cpp
        src/engine/ModAPI.h
)

target_compile_features(DyingLightGame PUBLIC cxx_std_20)
target_include_directories(DyingLightGame
        PRIVATE
        ${CMAKE_SOURCE_DIR}/libs/Engine/include
        ${CMAKE_SOURCE_DIR}/libs/Filesystem/include
        ${CMAKE_SOURCE_DIR}/libs/GameDLL/include
        ${CMAKE_SOURCE_DIR}/libs/Steam/include
        resources
        src
)

CPMAddPackage("gh:BasedInc/libhat@0.9.0")
CPMAddPackage("gh:zyantific/zydis@4.1.1")
CPMAddPackage("gh:cursey/safetyhook@0.6.9")
CPMAddPackage(NAME nlohmann_json GITHUB_REPOSITORY nlohmann/json VERSION 3.12.0)
CPMAddPackage("gh:ocornut/imgui@1.90.4")

if (imgui_ADDED OR imgui_SOURCE_DIR)
    target_sources(DyingLightGame PRIVATE
            ${imgui_SOURCE_DIR}/imgui.cpp
            ${imgui_SOURCE_DIR}/imgui_draw.cpp
            ${imgui_SOURCE_DIR}/imgui_tables.cpp
            ${imgui_SOURCE_DIR}/imgui_widgets.cpp
            ${imgui_SOURCE_DIR}/backends/imgui_impl_win32.cpp
            ${imgui_SOURCE_DIR}/backends/imgui_impl_dx11.cpp
    )
    target_include_directories(DyingLightGame PUBLIC
            ${imgui_SOURCE_DIR}
            ${imgui_SOURCE_DIR}/backends
    )
endif()
target_link_libraries(DyingLightGame
        PRIVATE
        libhat::libhat
        safetyhook::safetyhook
        nlohmann_json::nlohmann_json

        ChromeEngine::Engine
        ChromeEngine::GameDLL
        ChromeEngine::Filesystem
        Steam::API
        d3d11
        dxgi
)