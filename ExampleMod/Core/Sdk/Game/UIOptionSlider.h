#pragma once

class UIOptionSlider {
public:
    char padding[0xAC];
    int maxValue;  // Offset 0xAC
    int minValue;  // Offset 0xB0
};