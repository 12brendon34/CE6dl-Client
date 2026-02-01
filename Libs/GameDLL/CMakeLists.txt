add_library(ChromeEngine::GameDLL SHARED IMPORTED GLOBAL
        Include/games/DeadIsland/Game/Game/SessionCooperativeDI.h
        Include/games/DeadIsland/Game/Game/BozakMode.h
        Include/games/DeadIsland/Game/Game/DynamicObject.h
        Include/games/DeadIsland/Game/Game/DynamicObjectsManager.h
        Include/games/DeadIsland/Game/Game/GameDI.h
        Include/games/DeadIsland/Game/Game/LevelDI.h
        Include/games/DeadIsland/Game/Game/LocalClientDI.h
        Include/games/DeadIsland/Game/Game/LogicalPlayer.h
        Include/games/DeadIsland/Game/Game/SessionDI.h
        Include/games/DeadIsland/Game/Player/PlayerDI.h
        Include/games/DeadIsland/Game/Camera/CameraFPPDI.h
        Include/games/DeadIsland/Game/Camera/BaseCameraDI.h
        Include/games/GameEngine/engine/camera.h)

set_target_properties(ChromeEngine::GameDLL PROPERTIES
        IMPORTED_IMPLIB "${CMAKE_CURRENT_LIST_DIR}/gamedll_x64_rwdi.lib"
        IMPORTED_LOCATION "${CMAKE_CURRENT_LIST_DIR}/gamedll_x64_rwdi.dll"
)

target_include_directories(ChromeEngine::GameDLL INTERFACE
        Include
)
