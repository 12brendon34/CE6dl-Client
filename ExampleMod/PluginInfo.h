#pragma once
class IGame;

extern const char* const kPluginName;
extern "C" __declspec(dllexport) const char* GetPluginName();
extern "C" __declspec(dllexport) void PreInitialize(std::string ModPath);
extern "C" __declspec(dllexport) void PostInitialize(IGame* pIGame);

inline int g_maxFov = 40; //Default Value