cmake_minimum_required(VERSION 3.20)
project(MFCProject LANGUAGES CXX)

find_package(MFC)
if (NOT MFC_FOUND)
    message(STATUS "Install MFC!!!!!!!")
    return()
endif()

include(${CMAKE_SOURCE_DIR}/cmake/CPM.cmake)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_MFC_FLAG 2)

add_executable(MFCProject WIN32
        resources/targetver.h
        resources/Resource.h
        resources/MFCApplication.rc
        src/MFCApplication.cpp
        src/MFCApplication.h
        src/MainFrame.cpp
        src/MainFrame.h
        src/ChildView.cpp
        src/ChildView.h
)
target_compile_features(MFCProject PUBLIC cxx_std_20)
target_compile_definitions(MFCProject PRIVATE _AFXDLL)

target_include_directories(MFCProject
        PRIVATE
        ${CMAKE_SOURCE_DIR}/libs/Engine/include
        ${CMAKE_SOURCE_DIR}/libs/Filesystem/include
        ${CMAKE_SOURCE_DIR}/libs/GameDLL/include
        ${CMAKE_SOURCE_DIR}/libs/Steam/include
        resources
        src
)
target_link_libraries(MFCProject
        PRIVATE
        ChromeEngine::Engine
        ChromeEngine::GameDLL
        ChromeEngine::Filesystem
        Steam::API
)