#pragma once

#include "cpu.hpp"
#include "display.hpp"
#include "memory.hpp"
#include <string>
#include <fstream>
#include <iostream>
class Chip8{

    private:
        CPU cpu;
        Display display;
        Memory memory;
        void Load(std::string filename);
        typedef void (Chip8::*firstBit)(uint16_t);
        firstBit opcodes[16];
        void  _0(uint16_t _12LSb),  _1(uint16_t _12LSb),  _2(uint16_t _12LSb),  _3(uint16_t _12LSb);
        void  _4(uint16_t _12LSb),  _5(uint16_t _12LSb),  _6(uint16_t _12LSb),  _7(uint16_t _12LSb);
        void  _8(uint16_t _12LSb),  _9(uint16_t _12LSb),  _A(uint16_t _12LSb),  _B(uint16_t _12LSb);
        void  _C(uint16_t _12LSb),  _D(uint16_t _12LSb),  _E(uint16_t _12LSb),  _F(uint16_t _12LSb);
    public:
        Chip8(std::string filename); 
        void Cycle();
        void executeOpcode(uint16_t opcode);
};