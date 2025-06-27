#pragma once

#ifdef _DEBUG
#  define dbgprintf(...) fprintf(stdout, __VA_ARGS__)
#else
#  define dbgprintf(...) (void)NULL
#endif

// Standard library headers
#include <algorithm>
#include <cstdio>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>

// Windows headers
#include <Windows.h>
#include <shlobj_core.h>
#include <Psapi.h>

//common typedef
typedef unsigned int    uint;
