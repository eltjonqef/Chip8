#pragma once

#include <stdint.h>
#include <string.h>

class CPU{

    private:
        uint8_t V[16];
        uint16_t i;
        uint8_t sound_timer;
        uint8_t delay_timer;
        uint16_t pc;
        uint8_t sp;
        
    public:
        CPU();
        
};