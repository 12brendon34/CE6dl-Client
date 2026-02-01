//
// Created by Brendon on 1/15/2026.
//

#pragma once

namespace Mount {
    class IMountHelper {
    public:
        virtual ~IMountHelper();
        //virtual void Func_00(); // FUN_180257140
        virtual void Func_01(); // LAB_180257230
        virtual void Func_02(); // FUN_180258CB0
        virtual void Func_03(); // FUN_180258D20
        virtual void Func_04(); // LAB_1807D6F10
        virtual void Func_05(); // FUN_1802587E0
        virtual void Func_06(); // FUN_180258AE0
        virtual void Func_07(); // LAB_180258B00
        virtual void Func_08(); // FUN_1802570D0
        virtual void Func_09(); // FUN_180259520
        virtual void Func_10(); // LAB_180259A50
        virtual void Func_11(); // LAB_180259AD0
        virtual void Func_12(); // Stripped
        virtual void Func_13(); // LAB_18025A550
        virtual void Func_14(); // DAT_1808EAAD0
    };

    IMountHelper* CreateMountHelper(const char* param1, const char* param2, const char* param3);
    void DestroyMountHelper(IMountHelper* helper);
}