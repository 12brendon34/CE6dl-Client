#pragma once
#include "pch.h"

namespace ttl {
    template <typename T>
    class string_base;

    template <>
    class string_base<char> {
        char* m_Buffer;
        uint m_Size;
        uint m_Capacity;

    public:
        // Constructor (with basic initialization)
        explicit string_base(const char* str = "") {
            m_Size = 0;
            m_Capacity = 16; // Default capacity
            m_Buffer = new char[m_Capacity];

            // Copy the input string to the buffer
            while (str[m_Size] != '\0') {
                if (m_Size + 1 > m_Capacity) {
                    m_Capacity *= 2;
                    char* newBuffer = new char[m_Capacity];
                    for (uint i = 0; i < m_Size; ++i) {
                        newBuffer[i] = m_Buffer[i];
                    }
                    delete[] m_Buffer;
                    m_Buffer = newBuffer;
                }
                m_Buffer[m_Size] = str[m_Size];
                ++m_Size;
            }
            m_Buffer[m_Size] = '\0'; // Null-terminate
        }

        // Destructor to free memory
        ~string_base() {
            delete[] m_Buffer;
        }
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