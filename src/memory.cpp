#include "memory.hpp"

Memory::Memory(){

    memset(memory, 0, sizeof(memory));
}

void Memory::setMemory(int index, uint8_t value){

    memory[index]=value;
}

uint8_t Memory::getMemory(int index){
    
    return memory[index];
}

void Memory::setStack(int index, uint16_t value){
    stack[index]=value;
}

uint16_t Memory::getStack(int index){
    return stack[index];
}