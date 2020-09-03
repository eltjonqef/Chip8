#include "cpu.hpp"

CPU::CPU(){

    memset(V, 0, sizeof(V));
    i=0x0;
    sound_timer=0x0;
    delay_timer=0x0;
    pc=0x200;
    sp=0x0;
}

void CPU::setPC(uint16_t _pc){
    pc=_pc;
    
}

uint16_t CPU::getPC(){
    return pc;
}

void CPU::setSP(uint8_t _sp){
    sp=_sp;
}

uint8_t CPU::getSP(){
    return sp;
}

void CPU::setRegister(int index, uint8_t value){
    V[index]=value;
}

uint8_t CPU::getRegister(int index){
    return V[index];
}

void CPU::setI(uint16_t i){
    i=i;
}

uint16_t CPU::getI(){
    return i;
}