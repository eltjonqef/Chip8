#pragma once

#include <stdint.h>
#include <string.h>
#include <vector>
typedef void (*firstBit)(uint16_t);

class CPU{

    private:
        uint8_t V[16];
        uint16_t i;
        uint8_t sound_timer;
        uint8_t delay_timer;
        uint16_t pc;
        uint8_t sp;
        
        //First 4 bits of instruction
        void  _0(uint16_t opcode),  _1(uint16_t opcode),  _2(uint16_t opcode),  _3(uint16_t opcode);
        void  _4(uint16_t opcode),  _5(uint16_t opcode),  _6(uint16_t opcode),  _7(uint16_t opcode);
        void  _8(uint16_t opcode),  _9(uint16_t opcode),  _A(uint16_t opcode),  _B(uint16_t opcode);
        void  _C(uint16_t opcode),  _D(uint16_t opcode),  _E(uint16_t opcode),  _F(uint16_t opcode);

        //Last 4 bits of instruction with first 4 bits=0
        void  _00E0(),  _00EE();
        
    public:
        CPU();
        void setPC(uint16_t pc);
        uint16_t getPC();
        std::vector<void> opcodes;
};