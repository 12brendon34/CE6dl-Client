#pragma once

#ifdef _DEBUG
#  define dbgprintf(...) fprintf(stderr, __VA_ARGS__)
#else
#  define dbgprintf(...) (void)NULL
#endif

namespace Utils
{
	void InitConsole();

	void MsgBoxExit(UINT nType, LPCSTR lpCaption, LPCSTR sz, ...);

	std::string GetWorkingDirectory();

	HMODULE LoadLibrarySimple(LPCSTR lpModuleName);
}