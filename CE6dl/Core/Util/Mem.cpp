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
}