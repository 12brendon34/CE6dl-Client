//
// Created by Brendon on 1/12/2026.
//


#include <cstdint>
#include "engine/Export.h"
#include "engine/engine/Rtti/RTTI.h"

class IGame;

class ENGINE_API CGame {
public:
    static CRTTI m_RTTI;

    char pad_0000[24]; //0x0000
    IGame *m_IGame;

    char pad_0028[88]; //0x0028
    class N000005A9 *N00000066; //0x0098
    char pad_00A0[104]; //0x00A0
    int32_t N00000075; //0x0110
    float N00000463; //0x0114
    float N00000076; //0x0118
    int32_t N00000465; //0x011C
    int32_t N00000077; //0x0120
    int32_t N00000467; //0x0124
    char pad_0128[680]; //0x0128
    class N00000471 *N000000CD; //0x03D0
    char *N000000CE; //0x03D8
    int32_t N000000CF; //0x03E0
    int32_t N0000053F; //0x03E4
    char *N000000D0; //0x03E8
    int32_t N000000D1; //0x03F0
    int32_t N00000545; //0x03F4
    char pad_03F8[16]; //0x03F8
    int32_t N000000D4; //0x0408
    char pad_040C[60]; //0x040C
    int32_t N000000DC; //0x0448
    char pad_044C[92]; //0x044C
    wchar_t *N000000E8; //0x04A8
    int32_t N000000E9; //0x04B0
    int32_t N0000055F; //0x04B4
    char pad_04B8[16]; //0x04B8
    int32_t N000000EC; //0x04C8
    char pad_04CC[28]; //0x04CC
    int32_t N000000F0; //0x04E8
    char pad_04EC[20]; //0x04EC
    char N00000557[260]; //0x0500
    char pad_0604[68]; //0x0604
    int32_t N00000563; //0x0648
    char pad_064C[96]; //0x064C
    int32_t N00000109; //0x06AC
    char pad_06B0[4]; //0x06B0
    int32_t N0000010A; //0x06B4
    char pad_06B8[24]; //0x06B8
    int32_t N0000061F; //0x06D0
    char pad_06D4[1264]; //0x06D4

    virtual ~CGame();
}; //Size: 0x0BA8
static_assert(sizeof(CGame) == 0xBA8);
