//
// Created by Brendon on 2/8/2026.
//

#pragma once

class CEditorData {
    public:
    virtual ~CEditorData();
    //buncha stuff

    char pad_0000[0x114];
};
static_assert(sizeof(CEditorData) == 0x120);