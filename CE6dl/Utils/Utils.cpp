#include <pch.h>
#include "Utils.h"

namespace Utils
{
	void InitConsole()
	{
		FILE* fp;
		if (!AttachConsole(ATTACH_PARENT_PROCESS)) {
			AllocConsole();
		}
		freopen_s(&fp, "CONOUT$", "w", stdout);
		freopen_s(&fp, "CONOUT$", "w", stderr);
	}

	void MsgBoxExit(UINT nType, LPCSTR lpCaption, LPCSTR sz, ...) 
	{
		char ach[512];
		va_list args;
		va_start(args, sz);
		(void)wvsprintf(ach, sz, args);
		(void)MessageBox(nullptr, ach, lpCaption, nType);
		ExitProcess(0);
	}

	HMODULE LoadLibrarySimple(LPCSTR lpModuleName)
	{
		HMODULE Handle = LoadLibrary(lpModuleName);
		if (Handle)
			(void)dbgprintf("Found %s BaseAddress at: %p\n", lpModuleName, Handle);
		else
			Utils::MsgBoxExit(MB_ICONERROR, "Exiting", "Unable to create handle for %s", lpModuleName);

		return Handle;
	}

	bool CreateFolder(const std::filesystem::path& path) 
	{
		while (!std::filesystem::exists(path)) {
			// Attempt to create the directory
			try {
				if (std::filesystem::create_directory(path)) {
					return true;
				}
			}
			catch (const std::exception& e) {
				throw std::runtime_error("Failed to create directory: " + std::string(e.what()));
			}
		}
		return false;
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

	//https://en.cppreference.com/w/cpp/string/byte/tolower
	std::string str_tolower(std::string s)
	{
		std::transform(s.begin(), s.end(), s.begin(),
			[](unsigned char c) { return std::tolower(c); }
		);
		return s;
	}

	std::string RemoveSuffix(const std::string& input, const std::string& suffix) {
		if (input.size() >= suffix.size() &&
			input.compare(input.size() - suffix.size(), suffix.size(), suffix) == 0) {
			return input.substr(0, input.size() - suffix.size());
		}
		return input; //return if no match
	}
}