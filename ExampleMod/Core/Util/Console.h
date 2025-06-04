#pragma once

namespace Utils {
    // Initializes a console window.
    // Attaches to the parent process's console if available,
    // otherwise allocates a new one. Redirects stdout and stderr.
    void InitConsole();
}
