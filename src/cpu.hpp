#pragma once

#include <stdint.h>
#include <string.h>
#include <vector>
#include <iostream>
#include "display.hpp"
#include "memory.hpp"
class CPU{

    private:
        uint8_t V[16];
        uint16_t i;
        uint8_t sound_timer;
        uint8_t delay_timer;
        uint16_t pc;
        uint8_t sp;
        typedef void (CPU::*firstBit)(uint16_t, Display*, Memory*);
        firstBit opcodes[16];
        void  _0(uint16_t _12LSb, Display *display, Memory *memory);
        void  _1(uint16_t _12LSb, Display *display, Memory *memory);
        void  _2(uint16_t _12LSb, Display *display, Memory *memory);
        void  _3(uint16_t _12LSb, Display *display, Memory *memory);
        void  _4(uint16_t _12LSb, Display *display, Memory *memory);
        void  _5(uint16_t _12LSb, Display *display, Memory *memory);
        void  _6(uint16_t _12LSb, Display *display, Memory *memory);
        void  _7(uint16_t _12LSb, Display *display, Memory *memory);
        void  _8(uint16_t _12LSb, Display *display, Memory *memory);
        void  _9(uint16_t _12LSb, Display *display, Memory *memory);
        void  _A(uint16_t _12LSb, Display *display, Memory *memory);
        void  _B(uint16_t _12LSb, Display *display, Memory *memory);
        void  _C(uint16_t _12LSb, Display *display, Memory *memory);
        void  _D(uint16_t _12LSb, Display *display, Memory *memory);
        void  _E(uint16_t _12LSb, Display *display, Memory *memory);
        void  _F(uint16_t _12LSb, Display *display, Memory *memory);
        
    public:
        CPU();
        void setPC(uint16_t pc);
        uint16_t getPC();
        void setSP(uint8_t sp);
        uint8_t getSP();
        void executeOpcode(uint16_t opcode);
        void setRegister(int index, uint8_t value);
        uint8_t getRegister(int index);
        void setI(uint16_t i);
        uint16_t getI();
        void executeOpcode(uint16_t opcode, Display *display, Memory *memory);
};