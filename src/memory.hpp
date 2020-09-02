#pragma once

#include <stdint.h>
#include <string.h>

class Memory{

    private:
        uint8_t memory[4096];
        uint16_t stack[16];

    public:
        Memory();
        void setMemory(int index, uint8_t value);
        uint8_t getMemory(int index);
        void setStack(int index, uint16_t value);
        uint16_t getStack(int index);
};