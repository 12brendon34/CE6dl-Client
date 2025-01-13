#pragma once

#ifdef _DEBUG
#  define dbgprintf(...) fprintf(stdout, __VA_ARGS__)
#else
#  define dbgprintf(...) (void)NULL
#endif

namespace Utils
{
	void InitConsole();

	void MsgBoxExit(UINT nType, LPCSTR lpCaption, LPCSTR sz, ...);

	HMODULE LoadLibrarySimple(LPCSTR lpModuleName);

	bool CreateFolder(const std::string& path);

	std::string GetWorkingDirectory();

	std::string str_tolower(std::string s);
}