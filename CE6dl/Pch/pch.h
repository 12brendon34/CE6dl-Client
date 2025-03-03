#pragma once

// Standard library headers
#include <algorithm>
#include <cstdio>
#include <filesystem>
#include <iostream>
#include <vector>

// Windows headers
#include <Windows.h>
#include <shlobj_core.h>

// Third-party
#include "../SDK/Steam/steam_api.h"
#include "../Core/Utils.h"

//common typedef
typedef unsigned int    uint;
typedef unsigned short    ushort;

//namespace fs = std::filesystem;
//Conflict with filesystem dll