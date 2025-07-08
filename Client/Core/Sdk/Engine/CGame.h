#include "IGame.h"

class cachedrdfile;

struct CVideoSettings {
    char reserved[188];  // Placeholder for video settings data
};

//malloc(0x1a8);
class CGameEditor {
    virtual __int64 FUN_18016a110(char* param_2, __int64 param_3, uint64_t param_4);
    virtual uint64_t FUN_18016a350(__int64 param_2);
    virtual __int64 FUN_18016a140(__int64* param_2);
    virtual void ReloadMaterials();
    virtual void* FUN_18016a370();
    virtual void* FUN_18016a5c0(char* param_2);
    virtual void* FUN_18016a5d0(uint64_t param_2, uint64_t param_3, __int64 param_4);
    virtual void* FUN_18016a0f0(uint64_t param_2);
    virtual uint64_t FUN_180169d40();
    virtual uint64_t FUN_180169d70(__int64* param_2, __int64 param_3);
    virtual __int64 FUN_180169e50(__int64* param_2, __int64 param_3);
    virtual void* ReleaseTexture(uint64_t param_2);
    virtual void* UpdateTexture(__int64 param_2, uint64_t param_3, uint64_t param_4, int param_5, int param_6, int param_7, int param_8, int param_9, uint64_t param_10, int param_11);
    virtual void* LoadTexture(char* param_2);
    virtual void* FUN_18016a080(float* param_2, uint param_3, float param_4, int param_5);
    virtual uint64_t FUN_18016abd0();
    virtual int GetHeight();
    virtual void* FUN_180169d20(uint64_t param_2);
    virtual uint64_t FUN_1801676a0(uint param_2);
    virtual uint64_t FUN_180167d20(uint64_t param_2, uint64_t param_3);
    virtual __int64* GetIgnoreTemplateMap();
    virtual uint64_t FUN_180167b00();
    virtual void* FUN_1801678e0(float* param_2, float* param_3, __int64 param_4, int param_5, int param_6, int param_7, int param_8);
    virtual void* FUN_1801677b0(float* param_2, __int64 param_3, int param_4, int param_5, int param_6, int param_7);
    virtual __int64 FUN_180167ae0(__int64 param_2);
    virtual void* FUN_180167b40();
    virtual __int64 FUN_180167bc0(class CRTTIObject* param_2, char param_3);
    virtual __int64 FUN_180167710(__int64* param_2, char param_3);
    virtual void* FUN_180167c70();
    virtual uint64_t FUN_180167cc0(int param_2);
    virtual void* FUN_180167d70();
    virtual class ENUM* GetFormat();
    virtual uint64_t FUN_180167dc0(int param_2);
    virtual __int64 FUN_180167d90();
    virtual void* FUN_180168050(uint64_t param_2, uint64_t param_3, uint64_t param_4);
    virtual void* FUN_180168170(__int64* param_2, uint64_t param_3, uint64_t param_4);
    virtual void* FUN_180167df0(__int64 param_2);
    virtual bool FUN_180168280(cachedrdfile* param_2, uint64_t param_3);
    virtual void* FUN_180168bc0();
    virtual void* FUN_1801683b0();
    virtual void* FUN_1801683d0();
    virtual void* FUN_1801683f0();
    virtual void* FUN_180168410();
    virtual uint64_t SaveGameModule(uint64_t param_2);
    virtual void* FUN_180168600();
    virtual void* FUN_180168610();
    virtual void* FUN_180168620();
    virtual void* FUN_180168750();
    virtual void* FUN_180168630(__int64 param_2, uint64_t param_3, uint64_t param_4);
    virtual void* FUN_1801688b0(uint64_t param_2, uint64_t param_3, uint64_t param_4, __int64 param_5);
    virtual uint64_t FUN_180168770(char* param_2);
    virtual uint FUN_180167ec0(__int64 param_2);
    virtual void* FUN_180168920(__int64* param_2);
    virtual __int64 FUN_1801689c0();
    virtual void* FUN_1801689d0(uint64_t param_2);
    virtual __int64 FUN_180168a20();
    virtual void* FUN_180168a30(uint64_t param_2);
    virtual __int64 FUN_180168a80();
    virtual void* FUN_180168a90(__int64* param_2);
    virtual __int64 FUN_180168b30();
    virtual void* FUN_180168b40(char* param_2, char* param_3);
    virtual __int64 FUN_180168b50();
    virtual uint64_t FUN_180168b60(uint64_t param_2, uint64_t param_3);
    virtual uint64_t FUN_18016a600();
    virtual uint64_t FUN_18016a630();
    virtual uint64_t FUN_18016a660();
    virtual void* FUN_18016a6c0(float* param_2);
    virtual uint64_t FUN_18016a690();
    virtual __int64* FUN_180168be0(__int64 param_2, char param_3);
    virtual void* FUN_180168d00(int param_2, int param_3);
    virtual void* FUN_180168d40(uint64_t param_2, uint64_t param_3);
    virtual uint64_t FUN_180168d80(uint64_t param_2);
    virtual uint FUN_180168e00(uint64_t param_2);
    virtual bool FUN_180168f40(class CRTTI* param_2, class CRTTI* param_3);
    virtual bool FUN_180168e70(uint64_t param_2, uint64_t param_3);
    virtual void* FUN_180168e40(uint64_t param_2);
    virtual void* FUN_18016aba0(__int64 param_2);
    virtual void* FUN_180169cf0(uint64_t param_2, __int64 param_3, uint64_t param_4);
    virtual void* FUN_18016a970();
    virtual void* FUN_18016a9b0();
    virtual void* FUN_18016a990();
    virtual int FUN_180168f90(char* param_2, uint64_t param_3, uint64_t param_4);
    virtual void* FUN_180169660();
    virtual void* FUN_180169670(uint64_t param_2);
    virtual uint64_t FUN_180168fb0(int param_2);
    virtual void* FUN_180168fe0(int param_2, uint64_t param_3);
    virtual void* UpdateRenderOptions(uint64_t param_2);
    virtual void* FUN_180169010();
    virtual void* SaveRenderOptions(uint64_t param_2);
    virtual void* FUN_180169120(char* param_2, uint64_t param_3, __int64 param_4);
    virtual void* SaveIkOptions(uint64_t param_2, uint64_t param_3);
    virtual uint64_t FUN_180169160();
    virtual void* FUN_180169400(char* param_2, uint64_t param_3, __int64 param_4);
    virtual void* FUN_180169c70();
    virtual uint64_t FUN_18016abc0();
    virtual void* FUN_18016ae60();

};


class CGame {
private:
    char* padding1[19];
    IGame* m_IGame;
    int64_t padding2[4];
    CVideoSettings* m_pVideoSettings;
    int64_t padding3[92];
    int64_t* m_pGameEditor;
    char padding4[32];
    int64_t* m_pAudioSettings;
    void* padding5[250];

public:
    // Add constructors, destructors, or methods as needed
};