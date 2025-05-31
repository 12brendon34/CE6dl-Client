#pragma once
#include "pch.h"


namespace ttl {
    template <typename T>
    class string_base;

    template <>
    class string_base<char> {
        std::unique_ptr<char[]> m_Buffer;
        uint m_Size;
        uint m_Capacity;

    public:
        explicit string_base(const char* str = "") {
            if (str == nullptr) {
                m_Size = 0;
                m_Capacity = 0;
                m_Buffer = nullptr;
            }
            else {
                m_Size = std::strlen(str);
                m_Capacity = m_Size + 1;

                m_Buffer = std::make_unique<char[]>(m_Capacity);
                std::memcpy(m_Buffer.get(), str, m_Size);
                m_Buffer[m_Size] = '\0';
            }
        }

        ~string_base() = default;

        // Return the C-string
        const char* c_str() const {
            return m_Buffer.get();
        }
    };


    typedef enum TYPE {
    };

    struct allocator {
        TYPE m_MemCategory;
    };


    class CRTTIconst {

    };

    template <typename T, typename Allocator>
        class list {
        public:
            class iterator;
            class const_iterator;
            class reverse_iterator;
            class const_reverse_iterator;
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



    //guess and shit
    template<int MemType, typename T>
    class vectorm {
    private:
        T* m_Data = nullptr;      // offset 0x0
        uint32_t m_Size = 0;      // offset 0x8
        uint32_t m_Capacity = 0;  // offset 0xC

    public:
        vectorm() = default;

        ~vectorm() {
            clear();
            if (m_Data) {
                free(m_Data);
                m_Data = nullptr;
            }
            m_Size = 0;
            m_Capacity = 0;
        }

        void push_back(const T& value) {
            if (m_Size >= m_Capacity) {
                grow();
            }
            m_Data[m_Size++] = value;
        }

        void clear() {
            for (uint32_t i = 0; i < m_Size; ++i) {
                m_Data[i].~T();
            }
            m_Size = 0;
        }

        size_t size() const {
            return m_Size;
        }

        T& operator[](size_t index) {
            if (index >= m_Size) throw std::out_of_range("Index out of bounds");
            return m_Data[index];
        }

        const T& operator[](size_t index) const {
            if (index >= m_Size) throw std::out_of_range("Index out of bounds");
            return m_Data[index];
        }

    private:
        void grow() {
            m_Capacity = m_Capacity ? m_Capacity * 2 : 4;
            m_Data = reinterpret_cast<T*>(realloc(m_Data, sizeof(T) * m_Capacity));
            if (!m_Data) throw std::bad_alloc();
        }
    };
}