#pragma once
#include <stdint.h>
#include <string.h>
#include <map>

class Keyboard
{
    public:
        std::map<int, bool> keys;
        Keyboard(/* args */);
        ~Keyboard();
};
