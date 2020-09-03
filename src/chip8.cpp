#include "chip8.hpp"


Chip8::Chip8(std::string filename){

    for(int i=0; i<80; i++){
        memory.setMemory(i, display.getFont(i));
    }
    Load(filename);
    opcodes[0]=&Chip8::_0;
    opcodes[1]=&Chip8::_1;
    opcodes[2]=&Chip8::_2;
    opcodes[3]=&Chip8::_3;
    opcodes[4]=&Chip8::_4;
    opcodes[5]=&Chip8::_5;
    opcodes[6]=&Chip8::_6;
    opcodes[7]=&Chip8::_7;
    opcodes[8]=&Chip8::_8;
    opcodes[9]=&Chip8::_9;
    opcodes[10]=&Chip8::_A;
    opcodes[11]=&Chip8::_B;
    opcodes[12]=&Chip8::_C;
    opcodes[13]=&Chip8::_D;
    opcodes[14]=&Chip8::_E;
    opcodes[15]=&Chip8::_F;
    srand (time(NULL));
}

void Chip8::Load(std::string filename){

    std::ifstream file(filename, std::ios::binary);
    uint8_t byte;
    int i=0;
    while(file>>byte){
        memory.setMemory(0x200+i, byte);
        i++;
    }
    file.close();
    Cycle();
}

void Chip8::Cycle(){

    uint16_t opcode= memory.getMemory(cpu.getPC()) << 8 | memory.getMemory(cpu.getPC()+1);
    executeOpcode(opcode);
    cpu.setPC(cpu.getPC()+2);
}

void Chip8::executeOpcode(uint16_t opcode){
    (this->*opcodes[(opcode & 0xF000) >>12])(opcode & 0x0FFF);
}

void Chip8::_0(uint16_t _12LSb){

    switch(_12LSb & 0x000F){
        case 0x0:
            std::cout<<"Clear Screen"<<std::endl;
            display.ClearDisplay();
            cpu.setPC(cpu.getPC()+2);
            break;

        case 0xE:
            std::cout<<"Return"<<std::endl;
            cpu.setPC(memory.getStack(cpu.getSP()));
            cpu.setSP(cpu.getSP()-1);
            break;
        
        default:
            std::cout<<"Unknown Instruction"<<std::endl;
            break;
    }
}

void Chip8::_1(uint16_t _12LSb){

    std::cout<<"Jump"<<std::endl;
    cpu.setPC(_12LSb);
}

void Chip8::_2(uint16_t _12LSb){

    std::cout<<"Call"<<std::endl;
    cpu.setSP(cpu.getSP()+1);
    memory.setStack(cpu.getSP(), cpu.getPC());
    cpu.setPC(_12LSb);
}

void Chip8::_3(uint16_t _12LSb){

    std::cout<<"Skip if equal (byte)"<<std::endl;
    if(cpu.getRegister((_12LSb & 0x0F00) >> 8)==(_12LSb & 0x00FF)){
        cpu.setPC(cpu.getPC()+4);
    }
    else{
        cpu.setPC(cpu.getPC()+2);
    }
}

void Chip8::_4(uint16_t _12LSb){

    std::cout<<"Skip if not equal (byte)"<<std::endl;
    if(cpu.getRegister((_12LSb & 0x0F00) >> 8)!=(_12LSb & 0x00FF)){
        cpu.setPC(cpu.getPC()+4);
    }
    else{
        cpu.setPC(cpu.getPC()+2);
    }
}

void Chip8::_5(uint16_t _12LSb){

    std::cout<<"Skip if not equal (register)"<<std::endl;
    if(cpu.getRegister((_12LSb & 0x0F00) >> 8)==cpu.getRegister((_12LSb & 0x00F0) >> 4)){
        cpu.setPC(cpu.getPC()+4);
    }
    else{
        cpu.setPC(cpu.getPC()+2);
    }
}

void Chip8::_6(uint16_t _12LSb){

    std::cout<<"Load"<<_12LSb<<std::endl;
    cpu.setRegister((_12LSb & 0x0F00)>>8, _12LSb & 0x00FF);
    cpu.setPC(cpu.getPC()+2);
}

void Chip8::_7(uint16_t _12LSb){

    std::cout<<"Add (byte)"<<_12LSb<<std::endl;
    cpu.setRegister((_12LSb & 0x0F00)>>8, cpu.getRegister((_12LSb & 0x0F00)>>8)+(_12LSb & 0x00FF));
    cpu.setPC(cpu.getPC()+2);
}

void Chip8::_8(uint16_t _12LSb){ 

    switch(_12LSb & 0x000F){
        case 0:
            cpu.setRegister((_12LSb & 0x0F00) >> 8, cpu.getRegister((_12LSb & 0x00F0) >> 4));
            break;

        case 1:
            cpu.setRegister((_12LSb & 0x0F00) >> 8, cpu.getRegister((_12LSb & 0x0F00) >> 8) | cpu.getRegister((_12LSb & 0x00F0) >> 4));
            break;

        case 2:
            cpu.setRegister((_12LSb & 0x0F00) >> 8, cpu.getRegister((_12LSb & 0x0F00) >> 8) & cpu.getRegister((_12LSb & 0x00F0) >> 4));
            break;

        case 3:
            cpu.setRegister((_12LSb & 0x0F00) >> 8, cpu.getRegister((_12LSb & 0x0F00) >> 8) ^ cpu.getRegister((_12LSb & 0x00F0) >> 4));
            break;

        case 4:
            cpu.setRegister(15, ((uint16_t)cpu.getRegister((_12LSb & 0x0F00) >> 8) + (uint16_t)cpu.getRegister((_12LSb & 0x00F0) >> 4))>255);
            cpu.setRegister((_12LSb & 0x0F00) >> 8, ((uint16_t)cpu.getRegister((_12LSb & 0x0F00) >> 8) + (uint16_t)cpu.getRegister((_12LSb & 0x00F0) >> 4)) & 0x00FF);
            break;

        case 5:
            cpu.setRegister(15, cpu.getRegister((_12LSb & 0x0F00) >> 8) > cpu.getRegister((_12LSb & 0x00F0) >> 4));
            cpu.setRegister((_12LSb & 0x0F00) >> 8, cpu.getRegister((_12LSb & 0x0F00) >> 8) - cpu.getRegister((_12LSb & 0x00F0) >> 4));
            break;

        case 6:
            cpu.setRegister(15, cpu.getRegister(15) & 0x1);
            cpu.setRegister((_12LSb & 0x0F00) >> 8, cpu.getRegister((_12LSb & 0x0F00) >> 8) >> 1);
            break;

        case 7:
            cpu.setRegister(15, cpu.getRegister((_12LSb & 0x0F00) >> 8) < cpu.getRegister((_12LSb & 0x00F0) >> 4));
            cpu.setRegister((_12LSb & 0x0F00) >> 8, cpu.getRegister((_12LSb & 0x00F0) >> 4) - cpu.getRegister((_12LSb & 0x0F00) >> 8));
            break;

        case 14:
            cpu.setRegister(15, cpu.getRegister((_12LSb & 0x0F00) >> 8) & 0x80);
            cpu.setRegister((_12LSb & 0x0F00) >> 8, cpu.getRegister((_12LSb & 0x0F00) >> 8) << 1);
            break;
        
        default: //Unknown Instruction
            std::cout<<"Unknown Instruction"<<std::endl;
            break;
    }
    cpu.setPC(cpu.getPC()+2);
}

void Chip8::_9(uint16_t _12LSb){

    if(cpu.getRegister((_12LSb & 0x0F00) >> 8)!=cpu.getRegister((_12LSb & 0x00F0) >> 4)){
        cpu.setPC(cpu.getPC()+4);
    }
    else{
        cpu.setPC(cpu.getPC()+2);
    }
}

void Chip8::_A(uint16_t _12LSb){

    cpu.setI(_12LSb);
    cpu.setPC(cpu.getPC()+2);
}

void Chip8::_B(uint16_t _12LSb){

    cpu.setPC(_12LSb + cpu.getRegister(0));
}

void Chip8::_C(uint16_t _12LSb){

    cpu.setRegister((_12LSb & 0x0F00) >> 8, (rand() % 256) & (_12LSb & 0x00FF));
    cpu.setPC(cpu.getPC()+2);
}

void Chip8::_D(uint16_t _12LSb){

    
}

void Chip8::_E(uint16_t _12LSb){

   
}

void Chip8::_F(uint16_t _12LSb){

   
}