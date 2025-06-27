#include <pch.h>
#include "Mem.h"
#include "Alert.h"

namespace Utils
{
	FARPROC GetProcAddress(HMODULE hModule, LPCSTR lpProcName) {
		#pragma warning(suppress : 6387)
		FARPROC Address = ::GetProcAddress(hModule, lpProcName);
		if (Address)
			(void)dbgprintf("Loaded Libary %s at: %p\n", lpProcName, Address);
		else
			Utils::MsgBoxExit(MB_ICONERROR, "Exiting", "Failed To Get Address of %s", lpProcName);

		return Address;
	}

	//also from echo
	#define INRANGE(x,a,b)   (x >= a && x <= b)
	#define GET_BITS( x )    (INRANGE((x&(~0x20)),'A','F') ? ((x&(~0x20)) - 'A' + 0xa) : (INRANGE(x,'0','9') ? x - '0' : 0))
	#define GET_BYTE( x )    (GET_BITS(x[0]) << 4 | GET_BITS(x[1]))

	//just gunna borrow echo's
	unsigned long long findSig(HMODULE hModule, const char* szSignature) {
		const char* pattern = szSignature;
		unsigned long long firstMatch = 0;

		static const unsigned long long rangeStart = (unsigned long long)hModule;//(unsigned long long)GetModuleHandleA("Minecraft.Windows.exe");

		MODULEINFO miModInfo;
		static bool init = false;

		if (!init) {
			init = true;
			GetModuleInformation(GetCurrentProcess(), (HMODULE)rangeStart, &miModInfo, sizeof(MODULEINFO));
		};

		static const unsigned long long rangeEnd = rangeStart + miModInfo.SizeOfImage;

		BYTE patByte = GET_BYTE(pattern);
		const char* oldPat = pattern;

		for (unsigned long long pCur = rangeStart; pCur < rangeEnd; pCur++) {

			if (!*pattern)
				return firstMatch;

			while (*(PBYTE)pattern == ' ')
				pattern++;

			if (!*pattern)
				return firstMatch;

			if (oldPat != pattern) {
				oldPat = pattern;
				if (*(PBYTE)pattern != '\?')
					patByte = GET_BYTE(pattern);
			};

			if (*(PBYTE)pattern == '\?' || *(BYTE*)pCur == patByte) {

				if (!firstMatch)
					firstMatch = pCur;

				if (!pattern[2])
					return firstMatch;

				pattern += 2;

			}

			else {

				pattern = szSignature;
				firstMatch = 0;

			};
		};

		return NULL;

	};
}