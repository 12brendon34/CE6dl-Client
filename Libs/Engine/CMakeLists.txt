add_library(ChromeEngine::Engine SHARED IMPORTED GLOBAL
        include/engine/Game/IGame.h
        include/engine/Game/Factory.h
        include/engine/Game/CGame.h
        include/engine/Kernel3D/Matrix.h
        include/engine/Lobby/Lobby.h
        include/engine/Lobby/LobbySteam.h
        include/engine/Cameras/IBaseCamera.h
        include/engine/ChromeTypes.h
        include/engine/Cameras/CBaseCamera.h
        include/engine/Kernel/ffmt.h
        include/engine/Kernel/ttl/String.h
        include/engine/engine/interfaces/ExportedEnums.h
        include/engine/engine/resourcemanagement/MountHelper.h
        include/engine/engine/Levels/ILevel.h
        include/engine/engine/Levels/CLevel.h
)

set_target_properties(ChromeEngine::Engine PROPERTIES
        IMPORTED_IMPLIB "${CMAKE_CURRENT_LIST_DIR}/engine_x64_rwdi.lib"
        IMPORTED_LOCATION "${CMAKE_CURRENT_LIST_DIR}/engine_x64_rwdi.dll"
)

target_include_directories(ChromeEngine::Engine INTERFACE
        include
)
