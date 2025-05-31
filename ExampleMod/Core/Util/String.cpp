#include <pch.h>
#include "String.h"

namespace Utils
{
	std::string str_tolower(std::string s) {
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
}
