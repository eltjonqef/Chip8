#pragma once

#include <stdint.h>
#include <string.h>

class Memory{

    public:
        uint8_t memory[4096];
        uint16_t stack[16];
        Memory();
};