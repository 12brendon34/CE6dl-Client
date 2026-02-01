add_library(Steam::API SHARED IMPORTED GLOBAL
        include/steam/isteamapplist.h
        include/steam/isteamapps.h
        include/steam/isteamappticket.h
        include/steam/isteamclient.h
        include/steam/isteamcontroller.h
        include/steam/isteamdualsense.h
        include/steam/isteamfriends.h
        include/steam/isteamgamecoordinator.h
        include/steam/isteamgameserver.h
        include/steam/isteamgameserverstats.h
        include/steam/isteamhtmlsurface.h
        include/steam/isteamhttp.h
        include/steam/isteaminput.h
        include/steam/isteaminventory.h
        include/steam/isteammatchmaking.h
        include/steam/isteammusic.h
        include/steam/isteammusicremote.h
        include/steam/isteamnetworking.h
        include/steam/isteamnetworkingmessages.h
        include/steam/isteamnetworkingsockets.h
        include/steam/isteamnetworkingutils.h
        include/steam/isteamparentalsettings.h
        include/steam/isteamps3overlayrenderer.h
        include/steam/isteamremoteplay.h
        include/steam/isteamremotestorage.h
        include/steam/isteamscreenshots.h
        include/steam/isteamugc.h
        include/steam/isteamuser.h
        include/steam/isteamuserstats.h
        include/steam/isteamutils.h
        include/steam/isteamvideo.h
        include/steam/matchmakingtypes.h
        include/steam/steam_api.h
        include/steam/steam_api_common.h
        include/steam/steam_api_flat.h
        include/steam/steam_api_internal.h
        include/steam/steam_gameserver.h
        include/steam/steamclientpublic.h
        include/steam/steamencryptedappticket.h
        include/steam/steamhttpenums.h
        include/steam/steamnetworkingfakeip.h
        include/steam/steamnetworkingtypes.h
        include/steam/steamps3params.h
        include/steam/steamtypes.h
        include/steam/steamuniverse.h
)

set_target_properties(Steam::API PROPERTIES
        IMPORTED_IMPLIB "${CMAKE_CURRENT_LIST_DIR}/steam_api64.lib"
        IMPORTED_LOCATION "${CMAKE_CURRENT_LIST_DIR}/steam_api64.dll"
)

target_include_directories(Steam::API INTERFACE
        include
)
