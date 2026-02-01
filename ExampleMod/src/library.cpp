//
// Created by Brendon on 1/29/2026.
//

#include "library.h"
#include <windows.h>
#include <iostream>

void OnLoad() {
    std::cout << "Hello, World!" << std::endl;
}

void OnUnload() {
    std::cout << "Goodbye, World!" << std::endl;
}

void OnPaint(const IGame *pIGame) {
    std::cout << "Paint" << std::endl;
}