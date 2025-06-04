#pragma once

namespace Utils {
    // Displays a simple message box with an OK button.
    // Returns the result of the MessageBox call.
    int Alert(const char* lpCaption, const char* lpText);


    // Displays a formatted message in a message box and exits the process.
    // nType: MessageBox type flags (e.g., MB_ICONERROR)
    // lpCaption: Caption of the message box
    // sz: Format string (like printf)
    void MsgBoxExit(UINT nType, LPCSTR lpCaption, LPCSTR sz, ...);
}
