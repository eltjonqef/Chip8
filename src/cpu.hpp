#pragma once

#include <stdint.h>
#include <string.h>
#include <vector>
#include <iostream>
#include "display.hpp"
#include "memory.hpp"
#include "keyboard.hpp"
class CPU{

    private:
        uint8_t V[16];
        uint16_t i;
        uint8_t sound_timer;
        uint8_t delay_timer;
        uint16_t pc;
        uint8_t sp;
        typedef void (CPU::*firstBit)(uint16_t, Display*, Memory*, Keyboard*);
        firstBit opcodes[16];
        void  _0(uint16_t opcode, Display *display, Memory *memory, Keyboard *keyboard);
        void  _1(uint16_t opcode, Display *display, Memory *memory, Keyboard *keyboard);
        void  _2(uint16_t opcode, Display *display, Memory *memory, Keyboard *keyboard);
        void  _3(uint16_t opcode, Display *display, Memory *memory, Keyboard *keyboard);
        void  _4(uint16_t opcode, Display *display, Memory *memory, Keyboard *keyboard);
        void  _5(uint16_t opcode, Display *display, Memory *memory, Keyboard *keyboard);
        void  _6(uint16_t opcode, Display *display, Memory *memory, Keyboard *keyboard);
        void  _7(uint16_t opcode, Display *display, Memory *memory, Keyboard *keyboard);
        void  _8(uint16_t opcode, Display *display, Memory *memory, Keyboard *keyboard);
        void  _9(uint16_t opcode, Display *display, Memory *memory, Keyboard *keyboard);
        void  _A(uint16_t opcode, Display *display, Memory *memory, Keyboard *keyboard);
        void  _B(uint16_t opcode, Display *display, Memory *memory, Keyboard *keyboard);
        void  _C(uint16_t opcode, Display *display, Memory *memory, Keyboard *keyboard);
        void  _D(uint16_t opcode, Display *display, Memory *memory, Keyboard *keyboard);
        void  _E(uint16_t opcode, Display *display, Memory *memory, Keyboard *keyboard);
        void  _F(uint16_t opcode, Display *display, Memory *memory, Keyboard *keyboard);
        
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
        void executeOpcode(uint16_t opcode, Display *display, Memory *memory, Keyboard *keyboard);
        void setDelayTimer(uint8_t delay_timer);
        uint8_t getDelayTimer();
        void setSoundTimer(uint8_t sound_timer);
        uint8_t getSoundTimer();
};