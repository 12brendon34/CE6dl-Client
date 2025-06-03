#include <pch.h>
#include "Directory.h"

namespace Utils
{
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

	std::filesystem::path GetWorkingDirectory() {
		char buffer[MAX_PATH];
		DWORD length = GetCurrentDirectoryA(MAX_PATH, buffer);

		if (length == 0) {
			std::cerr << "Error getting current directory\n";
			return {};
		}

		std::filesystem::path workingDirectory(buffer);

		// Ensure the path ends with a slash
		if (workingDirectory.filename() != "") {
			workingDirectory += "\\";
		}

		return workingDirectory;
	}
}
