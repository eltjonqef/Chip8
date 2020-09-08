#pragma once

#include "cpu.hpp"
#include "display.hpp"
#include "memory.hpp"
#include <string>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <time.h>
class Chip8{

    private:
        Display *display;
        Memory *memory;
        CPU *cpu;
        void Load(std::string filename);

    public:
        Chip8(std::string filename); 
        void Cycle();
        Display &getDisplay();
};