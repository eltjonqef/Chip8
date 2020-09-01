#include "cpu.hpp"

CPU::CPU(){

    memset(V, 0, sizeof(V));
    i=0x0;
    sound_timer=0x0;
    delay_timer=0x0;
    pc=0x200;
    sp=0x0;
    opcodes.push_back(_0);
    opcodes.push_back(_1);
    opcodes.push_back(_2);
    opcodes.push_back(_3);
    opcodes.push_back(_4);
    opcodes.push_back(_5);
    opcodes.push_back(_6);
    opcodes.push_back(_7);
    opcodes.push_back(_8);
    opcodes.push_back(_9);
    opcodes.push_back(_A);
    opcodes.push_back(_B);
    opcodes.push_back(_C);
    opcodes.push_back(_D);
    opcodes.push_back(_E);
    opcodes.push_back(_F);
}

void CPU::setPC(uint16_t _pc){
    pc=_pc;
    
}

uint16_t CPU::getPC(){
    return pc;
}

void CPU::_0(uint16_t opcode){

    uint8_t ___X=opcode & 0x0F;
    if(___X==0x0){ //CLS

    }
    else if(___X==0xE){ //RET
        
    }
    else{ //Unknown Instruction
        
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

    uint8_t ___X=opcode & 0x000F;
    if(___X==0){

    }
    else if(___X==1){

    }
    else if(___X==2){

    }
    else if(___X==3){

    }
    else if(___X==4){
        
    }
    else if(___X==5){
        
    }
    else if(___X==6){
        
    }
    else if(___X==7){
        
    }
    else if(___X==E){
        
    }
    else{
        
    }
}