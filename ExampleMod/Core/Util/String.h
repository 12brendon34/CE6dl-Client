#pragma once

namespace Utils
{
    // Converts a string to lowercase
    std::string str_tolower(std::string s);

    // Removes a specific suffix from a string if it exists
    std::string RemoveSuffix(const std::string& input, const std::string& suffix);

    // Converts PWSTR to std::string
    std::string PWSTRToString(PWSTR pwsz);

    // Convert Steam's language name to a web-friendly code (e.g., "english" -> "en")
    std::string ConvertSteamLangToWebLang(const std::string& steamLang);
}
