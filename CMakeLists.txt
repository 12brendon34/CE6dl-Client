cmake_minimum_required(VERSION 3.20)
project(DLCE LANGUAGES CXX)

add_definitions(-DSTEAM_PLATFORM=1)

add_subdirectory(libs/Engine)
add_subdirectory(libs/Filesystem)
add_subdirectory(libs/GameDLL)
add_subdirectory(libs/Steam)

add_subdirectory(DyingLightGame)
add_subdirectory(ExampleMod)
add_subdirectory(MFCProject)