#include <pch.h>
#include "IniConfig.h"

namespace Utils
{
    std::map<std::string, std::string> ReadSimpleIni(const std::filesystem::path& filepath) {
        std::ifstream file(filepath);
        std::map<std::string, std::string> result;

        std::string line;
        while (std::getline(file, line)) {
            line.erase(0, line.find_first_not_of(" \t"));
            line.erase(line.find_last_not_of(" \t\r\n") + 1);

            if (line.empty() || line[0] == ';' || line[0] == '#')
                continue;

            size_t eq = line.find('=');
            if (eq != std::string::npos) {
                std::string key = line.substr(0, eq);
                std::string val = line.substr(eq + 1);
                key.erase(0, key.find_first_not_of(" \t"));
                key.erase(key.find_last_not_of(" \t") + 1);
                val.erase(0, val.find_first_not_of(" \t"));
                val.erase(val.find_last_not_of(" \t") + 1);
                result[key] = val;
            }
        }

        return result;
    }
}
