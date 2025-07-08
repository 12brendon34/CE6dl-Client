#include <pch.h>
#include "String.h"
#include <map>

namespace Utils
{
	std::string str_tolower(std::string s) {
		std::transform(s.begin(), s.end(), s.begin(),
			[](unsigned char c) { return std::tolower(c); }
		);
		return s;
	}


	std::string RemoveSuffix(const std::string& input, const std::string& suffix) {
		if (input.size() >= suffix.size()) {
			std::string inputSuffix = input.substr(input.size() - suffix.size());
			if (str_tolower(inputSuffix) == str_tolower(suffix)) {
				return input.substr(0, input.size() - suffix.size());
			}
		}
		return input; // return if no match
	}

	std::string PWSTRToString(PWSTR pwsz) {
		if (!pwsz) 
			return "";

		int sizeNeeded = WideCharToMultiByte(CP_UTF8, 0, pwsz, -1, nullptr, 0, nullptr, nullptr);
		std::string result(sizeNeeded, 0);
		WideCharToMultiByte(CP_UTF8, 0, pwsz, -1, &result[0], sizeNeeded, nullptr, nullptr);
		result.pop_back(); // remove null terminator
		return result;
	}

	//match CGame::GetDefaultLocaleID, fixes a few things
	std::string ConvertSteamLangToWebLang(const std::string& steamLang) {
		static const std::map<std::string, std::string> langMap = {
			{"english", "En"},
			{"german", "De"},
			{"french", "Fr"},
			{"italian", "It"},
			{"spanish", "Es"},
			{"russian", "Ru"},
			{"japanese", "Jp"},
			{"polish", "Pl"},
			{"dutch", "Nl"},
			{"brazilian", "Br"},
			{"koreana", "Ko"},
			{"schinese", "Cn"},
			{"tchinese", "Tw"},
			{"latam", "El"},
			{"turkish", "Tr"},
			{"thai", "Th"},
			{"czech", "Cs"},
		};

		auto it = langMap.find(steamLang); 
		
		if (it != langMap.end()) {
			//found match
			return it->second;
		}
		else {
			//fallback en
			return "en";
		}

	}
}
