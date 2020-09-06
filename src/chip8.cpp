#include "chip8.hpp"


Chip8::Chip8(std::string filename){

    for(int i=0; i<80; i++){
        memory->setMemory(i, display->getFont(i));
    }
    Load(filename);
}

void Chip8::Load(std::string filename){

    std::ifstream file(filename, std::ios::binary | std::ios::ate);
    uint8_t byte;
    int size=(int)file.tellg();
    unsigned char buffer[size];
    file.seekg(0, file.beg);
    file.read((char*)(&buffer[0]), size);
    file.close();
    for(int i=0; i<size; i++){
        memory->setMemory(0x200+i, buffer[i]);
    }
    while(1){
        Cycle();
    }
}

void Chip8::Cycle(){

    uint16_t opcode= memory->getMemory(cpu->getPC()) << 8 | memory->getMemory(cpu->getPC()+1);
    cpu->executeOpcode(opcode, display, memory);
}

