#include "chip8.hpp"


Chip8::Chip8(std::string filename){

    for(int i=0; i<80; i++){
        memory->setMemory(i, display->getFont(i));
    }
    Load(filename);
}

void Chip8::Load(std::string filename){

    std::ifstream file(filename, std::ios::binary);
    uint8_t byte;
    int i=0;
    while(file>>byte){
        memory->setMemory(0x200+i, byte);
        i++;
    }
    file.close();
    Cycle();
}

void Chip8::Cycle(){

    uint16_t opcode= memory->getMemory(cpu->getPC()) << 8 | memory->getMemory(cpu->getPC()+1);
    cpu->executeOpcode(opcode, display, memory);
}

