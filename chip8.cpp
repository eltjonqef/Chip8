#include "chip8.hpp"


Chip8::Chip8(){

    CPU cpu;
    Display display;
    Memory memory;
    for(int i=0; i<80; i++){
        memory.setMemory(i, display.getFont(i));
    }
}