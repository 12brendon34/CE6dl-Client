#pragma once
#include <pch.h>
#include "../TTL.h"

class CGameEditor {
public:
    /*
    0x0	0x8	addr * undefined * *
    0x8	0x8	longlong * longlong *
    0x10	0x8	undefined8 * undefined8 *
    0x18	0x8	undefined8	undefined8
    0x20	0x4	undefined4	undefined4
    0x24	0x1 ? ? undefined
    0x25	0x1 ? ? undefined
    0x26	0x1 ? ? undefined
    0x27	0x1 ? ? undefined
    0x28	0x4	undefined4	undefined4
    0x2c	0x1 ? ? undefined
    0x2d	0x1 ? ? undefined
    0x2e	0x1 ? ? undefined
    0x2f	0x1 ? ? undefined
    0x30	0x1	undefined1	undefined1
    0x31	0x1 ? ? undefined
    0x32	0x1 ? ? undefined
    0x33	0x1 ? ? undefined
    0x34	0x1 ? ? undefined
    0x35	0x1 ? ? undefined
    0x36	0x1 ? ? undefined
    0x37	0x1 ? ? undefined
    0x38	0x8	longlong	longlong	m_pGame
    */
    LONGLONG* param2;        // param_2 of pretty much everything, including the exported Initialize function
    void* CCameraContainer;
    uint64_t unknown1;       // param_1[3]
    uint64_t unknown2;       // param_1[4]
    uint64_t value1;         // 0x17
    void* someFunctionPtr;   // &PTR_FUN_180839a50
    CGame* m_pGame;      // g_pGame

    virtual void IDK();
};


class vec2 {
public:
    float x;
    float y;
};

class IEngineImpl {
public:
    CGameEditor* m_pGameEditor;          // Pointer to CGameEditor instance
    float unknownFloat;        // Some float value (0x42c80000 = 100.0f)
    void* m_ConversionTools;     // Pointer to conversion tools
    void* ptr_FUN_18083ace8;   // Function pointer or object reference
    void* ptr_LAB_18083ab70;   // Another function pointer
    int unknownInt1;
    int unknownInt2;
    int unknownValues1[6];     // Array of unknown values (0x17 placeholders)
    int unknownValues2[6];
    int unknownValues3[6];
    int unknownValues4[6];
    int unknownInt3;
    int unknownInt4;
    int unknownValues5[6];
    int unknownValues6[6];
    int unknownValues7[6];
    int unknownValues8[6];
    int unknownFlag;
    int unknownCounter;
    void* ptr_FUN_18083bfb8;   // Another function pointer
    int unknownArray1[6];
    int unknownArray2[6];
    int unknownArray3[6];
    int unknownFinalFlag;

    virtual void* FUN_180170db0();
    virtual void Stripped();
    virtual void* FUN_180177990(float* param_2, uint64_t param_3, float* param_4, float* param_5, float* param_6);
    virtual uint64_t FUN_1801777d0();

    virtual void DestroyRayCache(class IRayCache* param_1);

    virtual uint64_t thunk_FUN_1804245f0();
    virtual uint64_t FUN_180177780();
    virtual LONGLONG FUN_1801777a0();
    virtual uint64_t FUN_1801777c0();
    virtual void* FUN_180176da0();
    virtual void* FUN_180176dc0(LONGLONG param_2);
    virtual uint64_t FUN_180176c90();
    virtual void* FUN_180176ca0(uint param_2);
    virtual ULONGLONG FUN_180176cb0(uint param_2);
    virtual void* FUN_180176cd0(int param_2);
    virtual uint64_t FUN_180176ce0(uint param_2);
    virtual ULONGLONG FUN_180176d00(uint param_2);
    virtual ULONGLONG FUN_180176d20(uint param_2);
    virtual ULONGLONG FUN_180176d50(uint param_2);
    virtual char* FUN_180176d80();

    virtual vec2* GetUVMin();

    virtual void* CrashSetPrintCallback(class _func_void_TYPE_char_ptr_char_ptr* param_2);
    virtual void* LogSetPrintCallback(class _func_void_TYPE_char_ptr_char_ptr* param_2);

    virtual uint64_t thunk_FUN_1807418d0(LONGLONG param_2);

    virtual char* GetDisplayMode(LONGLONG param_2);
    virtual uint64_t LoadTexture(char* param_2);
    virtual void* ReleaseTexture(uint64_t param_2);
    virtual void* DumpTextures(char* param_2);

    virtual void* FUN_180175b30(LONGLONG param_2, uint64_t param_3);
    virtual uint64_t FUN_180169d40();
    virtual uint64_t FUN_180175b60();

    //important lol
    virtual uint64_t GetRenderer();

    virtual bool FUN_180170350();
    virtual void* FUN_180170360(byte param_2);
    virtual void* FUN_180176810(float* param_2, float* param_3, float* param_4);
    virtual LONGLONG FUN_180175970(uint64_t param_2, int param_3);
    virtual void* FUN_180171960(void** param_2);
    virtual void* FUN_180171aa0(LONGLONG** param_2);
    virtual uint64_t FUN_1801758a0();
    virtual void* FUN_1801758b0(char* param_2, uint64_t param_3, ULONGLONG param_4);

    virtual class IImage* GetIImage();

    virtual void* FUN_180175880();

    virtual void* SetRenderUiInEditor(void* param_2);
    virtual uint64_t GetRenderSmtMaybeDebugRender();
    virtual uint64_t GetRenderSmt();
    virtual void* SetWPFInteropMode();
    virtual bool AreFlagsSet(int param_1);

    virtual void* FUN_180178130(uint64_t param_2);
    virtual void* FUN_180178140(uint64_t param_2);
    virtual uint64_t FUN_180178150();
    virtual void* FUN_180173cc0(uint64_t param_2, ULONGLONG param_3, uint64_t param_4);
    virtual void* FUN_180173de0();
    virtual void* FUN_180173e20();
    virtual void* FUN_180175ba0(uint64_t param_2);
    virtual uint64_t GetRTTIManager();
    virtual uint64_t GetRTTIManager_1();
    virtual void* FUN_1801709c0(uint64_t param_2);
    virtual void* FUN_180170990(uint64_t param_2);
    virtual uint64_t FUN_180170880(LONGLONG* param_2);
    virtual uint64_t FUN_1801707a0(uint64_t param_2);
    virtual void* FUN_180175bb0(LONGLONG* param_2, LONGLONG param_3, LONGLONG* param_4);
    virtual void* FUN_1801709f0(uint64_t param_2, LONGLONG param_3, void* param_4);
    virtual LONGLONG* FUN_180170ae0(LONGLONG* param_2, LONGLONG param_3, char param_4, LONGLONG param_5);
    virtual void* FUN_180170a70(uint64_t param_2, void* param_3, uint64_t param_4);
    virtual LONGLONG** FUN_180170c50(LONGLONG param_2, LONGLONG param_3, uint64_t param_4, char param_5, char param_6);
    virtual void* FUN_180170be0(uint64_t param_2, uint64_t param_3, void* param_4, void* param_5);
    virtual LONGLONG** FUN_180170ea0(LONGLONG param_2, LONGLONG param_3, char* param_4, uint64_t param_5, char param_6, void* param_7, char param_8, LONGLONG param_9);
    virtual void* FUN_180170e00(uint64_t param_2, uint64_t param_3, uint64_t param_4, void* param_5, void* param_6, void* param_7, uint64_t param_8);
    virtual LONGLONG** FUN_180171260(LONGLONG param_2, uint64_t param_3, uint64_t param_4);
    virtual void* FUN_180171210(uint64_t param_2, void* param_3);
    virtual LONGLONG FUN_180171480(uint64_t param_2, char param_3);
    virtual void* FUN_1801713c0();
    virtual class CRTTIObject* FUN_180171560(LONGLONG param_2, LONGLONG* param_3, LONGLONG param_4);
    virtual void* FUN_180171510(uint64_t param_2, uint64_t param_3);
    virtual void* FUN_1801718d0(LONGLONG param_2, class CRTTIObject* param_3, uint64_t param_4);
    virtual void* FUN_180171890(uint64_t param_2);
    virtual void* FUN_180171cb0(LONGLONG param_2, LONGLONG* param_3);
    virtual void* FUN_180171c70(uint64_t param_2);

    virtual void DeleteAnimAction(class IAnimAction* param_1);

    virtual void* FUN_180171e10();
    virtual void* FUN_1801766c0();
    virtual void* FUN_180176760(char param_2, uint64_t param_3, uint64_t param_4);
    virtual void* FUN_180172aa0();
    virtual void* FUN_180172ac0(uint64_t param_2);
    virtual void* FUN_180172af0();
    virtual void* FUN_180172b10(uint64_t param_2);
    virtual void* FUN_180172b40(LONGLONG* param_2, uint64_t param_3);
    virtual void* FUN_180172cc0(LONGLONG* param_2, uint64_t param_3);
    virtual void* FUN_180170370(float param_2);
    virtual uint64_t FUN_180170380();
    virtual void* FUN_180170390(float param_2);
    virtual uint64_t FUN_1801703a0();
    virtual void* FUN_180172d40(uint64_t param_2, uint64_t param_3);
    virtual uint64_t FUN_180172e50(uint64_t param_2, uint64_t param_3);
    virtual void* FUN_180172ed0(uint64_t param_2, float param_3);
    virtual void* FUN_180173170(uint64_t param_2, float param_3);
    virtual void* FUN_180173480(uint64_t param_2, float* param_3);
    virtual void* FUN_1801736b0(uint64_t param_2, float param_3);
    virtual void* FUN_1801737e0(uint64_t param_2);
    virtual LONGLONG FUN_180173a90(uint64_t param_2);
    virtual void* FUN_180173ad0();
    virtual void* FUN_180173ae0();
    virtual void* FUN_180173af0();
    virtual uint64_t FUN_180174f20(int param_2, char param_3);
    virtual uint64_t FUN_180173930(uint64_t param_2);
    virtual void* FUN_180173970(uint64_t param_2, uint64_t param_3);
    virtual void* FUN_1801739c0(uint64_t param_2);
    virtual uint64_t FUN_180173a40(uint64_t param_2);
    virtual void* FUN_180173a00(uint64_t param_2);
    virtual LONGLONG FUN_180173b10();
    virtual LONGLONG** FUN_180173b70(LONGLONG** param_2, void* param_3);
    virtual void* FUN_180173bf0();
    virtual void* FUN_180173c00(uint64_t param_2, uint64_t param_3, uint64_t param_4, uint64_t param_5, uint64_t param_6, uint64_t param_7);
    virtual uint64_t FUN_180172340(uint64_t param_2);
    virtual void* FUN_1801723a0(LONGLONG** param_2, int* param_3, int* param_4);
    virtual uint64_t FUN_180172970(LONGLONG param_2, byte** param_3);
    virtual uint64_t FUN_180176210(uint64_t param_2, LONGLONG* param_3);
    virtual uint64_t FUN_180176380(uint64_t param_2, LONGLONG* param_3);
    virtual LONGLONG FUN_1801764d0(LONGLONG** param_2, LONGLONG param_3);
    virtual LONGLONG FUN_180175800(LONGLONG param_2);
    virtual uint64_t FUN_180176550(LONGLONG param_2, LONGLONG param_3);
    virtual void* FUN_1801765e0(LONGLONG param_2, LONGLONG* param_3);
    virtual void* FUN_180173e30(uint64_t param_2);
    virtual LONGLONG* FUN_180173e50(LONGLONG param_2);
    virtual LONGLONG* FUN_180173f00(LONGLONG* param_2);
    virtual void* FUN_180174040(uint64_t param_2);
    virtual void* FUN_180174060(class CRTTIObject* param_2, LONGLONG* param_3, uint param_4);
    virtual void* FUN_180171e50(int param_2, char param_3, uint64_t param_4);
    virtual void* FUN_1801741e0(LONGLONG param_2, float* param_3, char param_4, uint64_t param_5);
    virtual void* FUN_180174e20(LONGLONG param_2, uint64_t param_3, uint64_t param_4, uint64_t param_5);
    virtual void* FUN_180175750(LONGLONG* param_2, uint64_t param_3);

    virtual void* CallsSomeRendererFunc();
    virtual void* SomeRenderFunck();
    virtual void* AlsoSomeRenderFunc();
    virtual void* Anotherone(void* param_2, void* param_3, void* param_4, uint64_t param_5);
    virtual void* Again();

    virtual void* FUN_1801750c0(int param_2, LONGLONG param_3, char param_4, uint64_t param_5, uint64_t param_6);
    virtual void* FUN_1801751b0(int param_2, LONGLONG param_3, char param_4, uint64_t param_5, uint64_t param_6, uint64_t param_7);
    virtual void* AnotherRenderFunction();

    virtual void* FUN_180175490(uint64_t param_2, uint64_t param_3, LPCSTR* param_4, uint64_t param_5, uint64_t param_6);
    virtual void* FUN_180175300(uint64_t param_2, uint64_t param_3, LPCSTR* param_4, uint64_t param_5);
    virtual uint64_t FUN_180175600(LPCSTR* param_2);
    virtual uint64_t FUN_180177620(uint64_t param_2);
    virtual void* FUN_180177630(uint64_t param_2);
    virtual uint64_t FUN_180177670(uint64_t param_2);
    virtual void* FUN_180177680(uint64_t param_2);
    virtual uint64_t FUN_1801776c0(uint64_t param_2);
    virtual void* FUN_1801776d0(uint64_t param_2);
    virtual uint64_t FUN_180177710();
    virtual void* FUN_180177720(uint64_t param_2);
    virtual uint64_t GetsSomethingFromRenderer();

    virtual void* FUN_180172110(uint64_t param_2, LONGLONG param_3, int param_4, int param_5, int param_6, int param_7, uint64_t param_8, int param_9);
    virtual void* FUN_180172070(uint64_t param_2, uint64_t param_3, uint64_t param_4, uint64_t param_5, uint64_t param_6, uint64_t param_7, uint64_t param_8);
    virtual void Stripped_1();
    virtual void* FUN_180172310();
    virtual void* SaveDDS(uint64_t param_2, uint64_t param_3, uint64_t param_4, uint64_t param_5, uint64_t param_6, uint64_t param_7, void* param_8, void* param_9);
    virtual void* FUN_1801767a0();
    virtual uint64_t GetTimer();
    virtual uint64_t GetInput();
    virtual uint64_t GetFactory();
    virtual uint64_t FUN_18016abc0();
    virtual uint64_t GetMeshMgr();
    virtual void* FUN_1801767d0();
    virtual uint64_t FUN_180176800();
    virtual void* FUN_1801761f0();

    virtual void* LoadMesh(char* param_2, uint64_t param_3, ULONGLONG param_4);

    virtual void* FUN_1801778e0(LONGLONG* param_2);
    virtual LONGLONG* FUN_1801778f0(char* param_2, char* param_3, uint64_t param_4, uint64_t param_5, uint64_t param_6);
    virtual void* FUN_180177980(LONGLONG param_2);
    virtual void* FUN_1801773b0(LONGLONG* param_2, LONGLONG* param_3);
    virtual void* FUN_180177300(uint64_t param_2, uint64_t param_3);
    virtual void* FUN_1801773c0(uint64_t param_2);
    virtual char* ThisJustReturnsTheStringNormalForSomeReason();
    virtual void* FUN_180177480(char* param_2);
    virtual void* FUN_1801774c0(LONGLONG* param_2, char param_3);
    virtual void* FUN_180177510(void** param_2);
    virtual void* FUN_1801771b0(LONGLONG** param_2, uint64_t param_3, void** param_4);
    virtual void* FUN_180177240();
    virtual uint64_t FUN_180177260();

    virtual uint64_t GetAnimScriptAliasDef();
    virtual void* FUN_1801774d0(LONGLONG param_2, uint64_t param_3);
    virtual char* GetVarScriptDef();
    virtual char* GetSkinScriptDefs();
    virtual class CRTTIObject* GetEngineRTTIObject();
    virtual uint64_t GetConversionTools_Maybe();

    virtual uint64_t FUN_180177730();
    virtual uint64_t FUN_180177760();
    virtual LONGLONG FUN_180168a20();
    virtual void* FUN_1801779c0(uint64_t param_2);
    virtual void* FUN_180177b20(void* param_2, void* param_3, void* param_4, uint64_t param_5);
    virtual void* FUN_180177a50(uint64_t param_2);
    virtual void* FUN_180177ab0(uint64_t param_2, uint64_t param_3);

    virtual void* ExecuteCommand(char* param_2);

    virtual void* FUN_180177b70(char* param_2, uint64_t param_3);
    virtual void* FUN_180177b90(uint64_t param_2);
    virtual void Stripped_2();

    virtual bool DoFxRender();
    virtual void EnableRenderFx(bool param_1);

    virtual bool FUN_180177c10();
    virtual void* FUN_180177c20(char param_2);
    virtual void* FUN_180177c30(UINT* param_2, uint64_t param_3, void* param_4);
    virtual ULONGLONG FUN_180177cb0(float param_2, float param_3, float param_4, uint param_5);
    virtual void* FUN_180177cf0(char* param_2);
    virtual uint64_t FUN_180177de0();
    virtual void* FUN_180177e00(uint64_t param_2, uint64_t param_3);
    virtual uint64_t FUN_180177e10();
    virtual void* FUN_180177e20(uint64_t param_2, uint64_t param_3);
    virtual uint64_t FUN_180177e30();
    virtual uint64_t FUN_180178160(uint64_t param_2);
    virtual uint64_t FUN_180177e40(LONGLONG param_2, LONGLONG* param_3);
    virtual char FUN_180177e70(float* param_2, LONGLONG* param_3);
    virtual bool CanBeEnabled(); //stripped, returns true
    virtual void* FUN_1801704f0();
    virtual uint64_t DeconstructorMaybe(uint param_2, uint64_t param_3, uint64_t param_4);
};






/*
//dont ask me, it's set to 0 in CEdytorApp::CEdytorApp
//IDK where its set, but in memory this is DW, maybe something calls FUN_140073080 and then sets it
char* DAT_141b70cf4 = (char*)"DW";

//some arg is passed with no way for me to figure out what the class is
//besides
//pcVar3 = (char *)(**(code **)(*param_2 + 8))(param_2);
*/

class IEditorImpl {
public:
    virtual void* FUN_1400a0b40(ULONGLONG param_2, uint64_t param_3, uint64_t param_4) { return nullptr; }
    virtual char* FUN_140073080() {
        return (char*)"DW";
    }
    virtual uint64_t FUN_1403e3b00() { return (uint64_t)nullptr; }
    virtual void* FUN_14008df40(uint64_t param_2) { return nullptr; }
    virtual void* FUN_14008df90(LONGLONG param_2, void* param_3) { return nullptr; }
    virtual void* FUN_14008e0e0(uint64_t param_2) { return nullptr; }
    virtual void* FUN_140207710() { return nullptr; }
    virtual void* FUN_14008d140(uint64_t param_2) { return nullptr; }
    virtual void* FUN_14008d230(uint64_t param_2) { return nullptr; }
    virtual void* FUN_14008d2c0(class CRTTIObject* param_2, char* param_3) { return nullptr; }
    virtual void* FUN_140207710_1() { return nullptr; }
    virtual void* FUN_14008ccf0() { return nullptr; }
    virtual void* FUN_14008d3f0(LONGLONG param_2, uint64_t param_3, uint64_t param_4) { return nullptr; }
    virtual void* FUN_14008d520(LONGLONG param_2) { return nullptr; }
    virtual void* FUN_14008daa0(float param_2, uint param_3) { return nullptr; }
    virtual void* FUN_14009d400(uint64_t param_2, uint64_t param_3) { return nullptr; }
    virtual void* FUN_14008de90(LONGLONG param_2) { return nullptr; }
    virtual uint64_t FUN_140076710(uint64_t param_2, short param_3) { return (uint64_t)nullptr; }
    virtual void* FUN_140075f70(LONGLONG* param_2, LONGLONG* param_3) { return nullptr; }
    virtual uint64_t FUN_140076300(LONGLONG* param_2, LONGLONG* param_3, uint64_t param_4, int param_5) { return (uint64_t)nullptr; }
    virtual void* FUN_1400a1230() { return nullptr; }
    virtual void* FUN_1400a1220() { return nullptr; }
    virtual uint64_t FUN_1400a1430() { return (uint64_t)nullptr; }
    virtual void* FUN_140097da0(char* param_2) { return nullptr; }
    virtual void* FUN_140097ea0(char* param_2) { return nullptr; }
    virtual void* FUN_140097fa0(char* param_2) { return nullptr; }
    virtual void* FUN_1400980a0(char* param_2) { return nullptr; }
    virtual void* FUN_1400981a0(char* param_2) { return nullptr; }
    virtual void* FUN_1400a1210() { return nullptr; }
    virtual void* FUN_1400a11e0(void* param_2, void* param_3, void* param_4, uint64_t param_5) { return nullptr; }
    virtual void* FUN_14009cc20(LONGLONG* param_2) { return nullptr; }
    virtual void* FUN_140093180(uint64_t param_2, uint64_t param_3, uint64_t param_4) { return nullptr; }
    virtual void* FUN_140093270() { return nullptr; }
    virtual void* FUN_14009d5b0(float* param_2, char param_3, uint64_t param_4) { return nullptr; }
    virtual byte FUN_14034b130() {
        return 0;
    }
    virtual void* FUN_14009ce20() { return nullptr; }
    virtual void* FUN_1400a11d0() { return nullptr; }
    virtual void* FUN_1400a11c0() { return nullptr; }
    virtual void* FUN_1400a11b0() { return nullptr; }
    virtual void* FUN_14009d5a0(class CRTTIObject* param_2, LONGLONG param_3) { return nullptr; }
    virtual void* FUN_14009ea20() { return nullptr; }
    virtual void* FUN_14009ea40(LONGLONG* param_2, uint64_t param_3) { return nullptr; }
    virtual void* FUN_14009d540(LONGLONG param_2, uint64_t param_3, uint64_t param_4) { return nullptr; }
    virtual void* FUN_14009d550(int param_2, uint64_t param_3, uint64_t param_4) { return nullptr; }
    virtual void* FUN_14009d560(int param_2, LONGLONG* param_3) { return nullptr; }
    virtual void* FUN_14009d570(int param_2, LONGLONG* param_3) { return nullptr; }
    virtual void* FUN_14009d580(int param_2) { return nullptr; }
    virtual void* FUN_14009d590(int param_2, LONGLONG param_3) { return nullptr; }
    virtual void* FUN_14009ebc0(void** param_2, char* param_3, void* param_4, void* param_5) { return nullptr; }
    virtual void* FUN_14009eba0(void** param_2, char* param_3, void* param_4, void* param_5) { return nullptr; }
    virtual void* FUN_14009eb80(void** param_2, char* param_3, void* param_4, void* param_5) { return nullptr; }
    virtual void* FUN_14009ebe0(uint param_2) { return nullptr; }
    virtual void* FUN_14009ec00(uint param_2, char* param_3) { return nullptr; }
    virtual void* FUN_14009ebf0(uint param_2, uint64_t param_3, char param_4) { return nullptr; }
};