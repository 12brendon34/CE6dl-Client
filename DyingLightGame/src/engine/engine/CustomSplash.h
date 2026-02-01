//
// Created by Brendon on 1/14/2026.
//
#pragma once
#include <windows.h>

static HINSTANCE g_hDllModule = nullptr;
static HBITMAP l_Bitmap = nullptr;
static HWND l_Splash = nullptr;
void ShowCustomSplashscreen(HINSTANCE hInstance, LPCSTR bitmap_res, UINT app_title_res, HICON icon);
void HideCustomSplashscreen();