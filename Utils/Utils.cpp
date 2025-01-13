#include <pch.h>
#include "Utils.h"

namespace Utils
{
	void InitConsole() {
		FILE* fp;
		if (!AttachConsole(ATTACH_PARENT_PROCESS)) {
			AllocConsole();
		}
		freopen_s(&fp, "CONOUT$", "w", stdout);
	}

	void MsgBoxExit(UINT nType, LPCSTR lpCaption, LPCSTR sz, ...) {

		char ach[512];
		va_list args;
		va_start(args, sz);
		(void)wvsprintf(ach, sz, args);
		(void)MessageBox(nullptr, ach, lpCaption, nType);
		ExitProcess(0);
	}

	std::string GetWorkingDirectory()
	{
		char buffer[MAX_PATH];

		// Get the current working directory
		DWORD length = GetCurrentDirectoryA(MAX_PATH, buffer);
		if (length == 0) {
			std::cerr << "Error getting current directory" << std::endl;
			return "";
		}

		std::string workingDirectory(buffer);

		// Append "\\" if not already present
		if (!workingDirectory.empty() && workingDirectory.back() != '\\') {
			workingDirectory += "\\";
		}

		return workingDirectory;
	}

	HMODULE LoadLibrarySimple(LPCSTR lpModuleName) {

		HMODULE Handle = LoadLibrary(lpModuleName);
		if (Handle)
			(void)dbgprintf("Found %s BaseAddress at: %p\n", lpModuleName, Handle);
		else
			Utils::MsgBoxExit(MB_ICONERROR, "Exiting", "Unable to create handle for %s", lpModuleName);

		return Handle;
	}
}