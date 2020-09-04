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
    srand (time(NULL));
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

void CPU::setDelayTimer(uint8_t delay_timer){
    delay_timer=delay_timer;
}

uint8_t CPU::getDelayTimer(){
    return delay_timer;
}

void CPU::setSoundTimer(uint8_t sound_timer){
    sound_timer=sound_timer;
}

uint8_t CPU::getSoundTimer(){
    return sound_timer;
}

void CPU::executeOpcode(uint16_t opcode, Display *display, Memory *memory){
    (this->*opcodes[(opcode & 0xF000) >>12])(opcode & 0x0FFF, display, memory);
}

void CPU::_0(uint16_t _12LSb, Display *display, Memory *memory){

    switch(_12LSb & 0x000F){
        case 0x0:
            std::cout<<"Clear Screen"<<std::endl;
            display->ClearDisplay();
            setPC(getPC()+2);
            break;

        case 0xE:
            std::cout<<"Return"<<std::endl;
            setPC(memory->getStack(getSP()));
            setSP(getSP()-1);
            break;
        
        default:
            std::cout<<"Unknown Instruction"<<std::endl;
            break;
    }
}

void CPU::_1(uint16_t _12LSb, Display *display, Memory *memory){

    std::cout<<"Jump"<<std::endl;
    setPC(_12LSb);
}

void CPU::_2(uint16_t _12LSb, Display *display, Memory *memory){

    std::cout<<"Call"<<std::endl;
    setSP(getSP()+1);
    memory->setStack(getSP(), getPC());
    setPC(_12LSb);
}

void CPU::_3(uint16_t _12LSb, Display *display, Memory *memory){

    std::cout<<"Skip if equal (byte)"<<std::endl;
    if(getRegister((_12LSb & 0x0F00) >> 8)==(_12LSb & 0x00FF)){
        setPC(getPC()+4);
        return;
    }
    setPC(getPC()+2);
}

void CPU::_4(uint16_t _12LSb, Display *display, Memory *memory){

    std::cout<<"Skip if not equal (byte)"<<std::endl;
    if(getRegister((_12LSb & 0x0F00) >> 8)!=(_12LSb & 0x00FF)){
        setPC(getPC()+4);
        return;
    }
    setPC(getPC()+2);
}

void CPU::_5(uint16_t _12LSb, Display *display, Memory *memory){

    std::cout<<"Skip if not equal (register)"<<std::endl;
    if(getRegister((_12LSb & 0x0F00) >> 8)==getRegister((_12LSb & 0x00F0) >> 4)){
        setPC(getPC()+4);
        return;
    }
    setPC(getPC()+2);
}

void CPU::_6(uint16_t _12LSb, Display *display, Memory *memory){

    std::cout<<"Load"<<_12LSb<<std::endl;
    setRegister((_12LSb & 0x0F00)>>8, _12LSb & 0x00FF);
    setPC(getPC()+2);
}

void CPU::_7(uint16_t _12LSb, Display *display, Memory *memory){

    std::cout<<"Add (byte)"<<_12LSb<<std::endl;
    setRegister((_12LSb & 0x0F00)>>8, getRegister((_12LSb & 0x0F00)>>8)+(_12LSb & 0x00FF));
    setPC(getPC()+2);
}

void CPU::_8(uint16_t _12LSb, Display *display, Memory *memory){ 

    switch(_12LSb & 0x000F){
        case 0:
            setRegister((_12LSb & 0x0F00) >> 8, getRegister((_12LSb & 0x00F0) >> 4));
            break;

        case 1:
            setRegister((_12LSb & 0x0F00) >> 8, getRegister((_12LSb & 0x0F00) >> 8) | getRegister((_12LSb & 0x00F0) >> 4));
            break;

        case 2:
            setRegister((_12LSb & 0x0F00) >> 8, getRegister((_12LSb & 0x0F00) >> 8) & getRegister((_12LSb & 0x00F0) >> 4));
            break;

        case 3:
            setRegister((_12LSb & 0x0F00) >> 8, getRegister((_12LSb & 0x0F00) >> 8) ^ getRegister((_12LSb & 0x00F0) >> 4));
            break;

        case 4:
            setRegister(15, ((uint16_t)getRegister((_12LSb & 0x0F00) >> 8) + (uint16_t)getRegister((_12LSb & 0x00F0) >> 4))>255);
            setRegister((_12LSb & 0x0F00) >> 8, ((uint16_t)getRegister((_12LSb & 0x0F00) >> 8) + (uint16_t)getRegister((_12LSb & 0x00F0) >> 4)) & 0x00FF);
            break;

        case 5:
            setRegister(15, getRegister((_12LSb & 0x0F00) >> 8) > getRegister((_12LSb & 0x00F0) >> 4));
            setRegister((_12LSb & 0x0F00) >> 8, getRegister((_12LSb & 0x0F00) >> 8) - getRegister((_12LSb & 0x00F0) >> 4));
            break;

        case 6:
            setRegister(15, getRegister(15) & 0x1);
            setRegister((_12LSb & 0x0F00) >> 8, getRegister((_12LSb & 0x0F00) >> 8) >> 1);
            break;

        case 7:
            setRegister(15, getRegister((_12LSb & 0x0F00) >> 8) < getRegister((_12LSb & 0x00F0) >> 4));
            setRegister((_12LSb & 0x0F00) >> 8, getRegister((_12LSb & 0x00F0) >> 4) - getRegister((_12LSb & 0x0F00) >> 8));
            break;

        case 14:
            setRegister(15, getRegister((_12LSb & 0x0F00) >> 8) & 0x80);
            setRegister((_12LSb & 0x0F00) >> 8, getRegister((_12LSb & 0x0F00) >> 8) << 1);
            break;
        
        default: //Unknown Instruction
            std::cout<<"Unknown Instruction"<<std::endl;
            break;
    }
    setPC(getPC()+2);
}

void CPU::_9(uint16_t _12LSb, Display *display, Memory *memory){

    if(getRegister((_12LSb & 0x0F00) >> 8)!=getRegister((_12LSb & 0x00F0) >> 4)){
        setPC(getPC()+4);
        return;
    }
    setPC(getPC()+2);
}

void CPU::_A(uint16_t _12LSb, Display *display, Memory *memory){

    setI(_12LSb);
    setPC(getPC()+2);
}

void CPU::_B(uint16_t _12LSb, Display *display, Memory *memory){

    setPC(_12LSb + getRegister(0));
}

void CPU::_C(uint16_t _12LSb, Display *display, Memory *memory){

    setRegister((_12LSb & 0x0F00) >> 8, (rand() % 256) & (_12LSb & 0x00FF));
    setPC(getPC()+2);
}

void CPU::_D(uint16_t _12LSb, Display *display, Memory *memory){

    //DISPLAY
}

void CPU::_E(uint16_t _12LSb, Display *display, Memory *memory){

    //KEYBOARD
}

void CPU::_F(uint16_t _12LSb, Display *display, Memory *memory){

    switch(_12LSb & 0x00FF){

        case 0x07:
            setRegister((_12LSb & 0x0F00)>>8, delay_timer);
            break;

        case 0x0A:
            //KEYBOARD
            break;
        
        case 0x15:
            setDelayTimer(getRegister((_12LSb & 0x0F00)>>8));
            break;
        
        case 0x18:
            setSoundTimer(getRegister((_12LSb & 0x0F00)>>8));
            break;

        case 0x1E:
            setI(getI()+getRegister((_12LSb & 0x0F00)>>8));
            break;

        case 0x29:
            //DISPLAY
            break;

        case 0x33:
            //DUNNO
            break;

        case 0x55:
            for(int i=0; i<((_12LSb & 0x0F00)>>8); i++){
                memory->setMemory(getI()+i, getRegister(i));
            }
            break;

        case 0x65:
            for(int i=0; i<((_12LSb & 0x0F00)>>8); i++){
                setRegister(i, memory->getMemory(getI()+i));
            }
            break;
    }
    setPC(getPC()+2);
}