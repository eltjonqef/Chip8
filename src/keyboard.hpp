#pragma once
#include <stdint.h>
#include <string.h>
#include <map>
#include <SDL2/SDL.h>

class Keyboard
{
    public:
        uint8_t keyboard[16];
        Keyboard(/* args */);
        ~Keyboard();
};
