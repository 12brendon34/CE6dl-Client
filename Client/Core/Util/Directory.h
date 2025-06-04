#pragma once

namespace Utils
{
    // Creates a directory at the specified path if it doesn't exist.
    bool CreateFolder(const std::filesystem::path& path);

    // Returns the current working directory with a trailing backslash.
    std::filesystem::path GetWorkingDirectory();
}
