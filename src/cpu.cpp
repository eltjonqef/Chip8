#include "cpu.hpp"

CPU::CPU(){

    memset(V, 0, sizeof(V));
    i=0x0;
    sound_timer=0x0;
    delay_timer=0x0;
    pc=0x200;
    sp=0x0;
    opcodes[0]=&CPU::_0;
    opcodes[1]=&CPU::_1;
    opcodes[2]=&CPU::_2;
    opcodes[3]=&CPU::_3;
    opcodes[4]=&CPU::_4;
    opcodes[5]=&CPU::_5;
    opcodes[6]=&CPU::_6;
    opcodes[7]=&CPU::_7;
    opcodes[8]=&CPU::_8;
    opcodes[9]=&CPU::_9;
    opcodes[10]=&CPU::_A;
    opcodes[11]=&CPU::_B;
    opcodes[12]=&CPU::_C;
    opcodes[13]=&CPU::_D;
    opcodes[14]=&CPU::_E;
    opcodes[15]=&CPU::_F;
}

void CPU::setPC(uint16_t _pc){
    pc=_pc;
    
}

uint16_t CPU::getPC(){
    return pc;
}

void CPU::_0(uint16_t opcode){

    switch(opcode & 0x0F){
        case 0x0: //CLS
            break;

        case 0x0E: //RET
            break;
        
        default: //Unknown Instruction
            break;
    }
}

void CPU::_1(uint16_t opcode){ //JP _XXX

    uint16_t _XXX=opcode & 0x0FFF;
}

void CPU::_2(uint16_t opcode){ //CALL _XXX

    uint16_t _XXX=opcode & 0x0FFF;
}

void CPU::_3(uint16_t opcode){ //SE V_X__=__XX

    uint8_t _X__ =opcode & 0x0F00;
    uint8_t __XX=opcode & 0x00FF;
}

void CPU::_4(uint16_t opcode){ //SE V_X__!=__XX

    uint8_t _X__ =opcode & 0x0F00;
    uint8_t __XX=opcode & 0x00FF;
}

void CPU::_5(uint16_t opcode){ //SE V_X__!=V__X_

    uint8_t _X__ =opcode & 0x0F00;
    uint8_t __X_=opcode & 0x00F0;
}

void CPU::_6(uint16_t opcode){ //LD V_X__<--__X_

    uint8_t _X__ =opcode & 0x0F00;
    uint8_t __XX=opcode & 0x00FF;
}

void CPU::_7(uint16_t opcode){ //ADD V_X__+=__XX

    uint8_t _X__ =opcode & 0x0F00;
    uint8_t __XX=opcode & 0x00FF;
}

void CPU::_8(uint16_t opcode){ 

    switch(opcode & 0x000F){
        case 0:
            break;

        case 1:
            break;

        case 2:
            break;

        case 3:
            break;

        case 4:
            break;

        case 5:
            break;

        case 6:
            break;

        case 7:
            break;

        case 14:
            break;
        
        default: //Unknown Instruction
            break;
    }
}

void CPU::_9(uint16_t opcode){

   
}

void CPU::_A(uint16_t opcode){

   
}

void CPU::_B(uint16_t opcode){

   
}

void CPU::_C(uint16_t opcode){

   
}

void CPU::_D(uint16_t opcode){

   
}

void CPU::_E(uint16_t opcode){

   
}

void CPU::_F(uint16_t opcode){

   
}