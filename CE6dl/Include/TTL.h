#pragma once
#include "pch.h"

namespace ttl {
    template <typename T>
    struct string_base;

    template <>
    struct string_base<char> {
        char* m_Buffer;
        uint m_Size;
        uint m_Capacity;
    };
    /*
    //CE 5
    typedef enum TYPE {
        Unknown = 0,
        AI = 1,
        AVI = 2,
        Anim = 3,
        AnimMixer = 4,
        AnimFile = 5,
        AnimScript = 6,
        Audio = 7,
        Speech = 8,
        SpeechBank = 9,
        BodyVis = 10,
        ChromeSpy = 11,
        Containers = 12,
        Decals = 13,
        Editor = 14,
        EditorInGame = 15,
        FX = 16,
        Files = 17,
        Flash = 18,
        Game = 19,
        GameObject = 20,
        Image = 21,
        Level = 22,
        LevelFilms = 23,
        Lights = 24,
        Lmaps = 25,
        Lobby = 26,
        Materials = 27,
        Mesh = 28,
        Mpl = 29,
        NavMesh = 30,
        Network = 31,
        Replication = 32,
        ReplicationHistory = 33,
        Objects = 34,
        ObjectsMorphs = 35,
        Parser = 36,
        Physics = 37,
        Player = 38,
        Quests = 39,
        RPacks = 40,
        RTTI = 41,
        Renderer = 42,
        RenderTargets = 43,
        Saves = 44,
        SimpleObjects = 45,
        Skills = 46,
        Strings = 47,
        System = 48,
        Terrain = 49,
        TTL = 50,
        UI = 51,
        UPlay = 52,
        Count = 53
    } TYPE;

    template <typename T>
    struct allocator {
        TYPE m_MemCategory;
    };

    template <typename T, typename Allocator = allocator<T>>
    class list {
        //idk bro
    };
    */

    template <typename T>
    class vector {
        //idk bro
    };
}