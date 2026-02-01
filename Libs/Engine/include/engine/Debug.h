//
// Created by Brendon on 1/12/2026.
//

//this is not actually from chrome engine
//just a helper
#pragma once
#include <cstdio>

#ifdef _DEBUG
#define dbgprintf(...) fprintf(stdout, __VA_ARGS__)
#else
#define dbgprintf(...) ((void)0)
#endif
