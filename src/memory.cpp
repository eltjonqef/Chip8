#include "memory.hpp"

Memory::Memory(){

    memset(memory, 0, sizeof(memory));
}

void Memory::setMemory(int index, uint8_t value){

    memory[index]=value;
}