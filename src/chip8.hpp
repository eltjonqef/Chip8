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
    public:
        Chip8(std::string filename); 
        void Cycle();
};