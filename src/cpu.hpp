#pragma once

#include <stdint.h>
#include <string.h>
#include <vector>
#include <iostream>
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
        void setPC(uint16_t pc);
        uint16_t getPC();
        void setSP(uint8_t sp);
        uint8_t getSP();
        void executeOpcode(uint16_t opcode);
        void setRegister(int index, uint8_t value);
        uint8_t getRegister(int index);
};