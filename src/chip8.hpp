#pragma once

#include "cpu.hpp"
#include "display.hpp"
#include "memory.hpp"
#include "keyboard.hpp"
#include <string>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <chrono>
#include <thread>
class Chip8{

    public:
        Display *display;
        Memory *memory;
        CPU *cpu;
        Keyboard *keyboard;
        void Load(std::string filename);
        Chip8(std::string filename); 
        void Cycle();
};