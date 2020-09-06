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

void CPU::setI(uint16_t _i){
    i=_i;
}

uint16_t CPU::getI(){
    return i;
}

void CPU::setDelayTimer(uint8_t _delay_timer){
    delay_timer=_delay_timer;
}

uint8_t CPU::getDelayTimer(){
    return delay_timer;
}

void CPU::setSoundTimer(uint8_t _sound_timer){
    sound_timer=_sound_timer;
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
            std::cout<<"00E0"<<std::endl;
            display->ClearDisplay();
            setPC(getPC()+2);
            break;

        case 0xE:
            std::cout<<"00EE"<<std::endl;
            setPC(memory->getStack(getSP()));
            setSP(getSP()-1);
            break;
        
        default:
            std::cout<<"Unknown Instruction 00EX"<<std::endl;
            break;
    }
}

void CPU::_1(uint16_t _12LSb, Display *display, Memory *memory){

    std::cout<<"1NNN"<<std::endl;
    setPC(_12LSb);
}

void CPU::_2(uint16_t _12LSb, Display *display, Memory *memory){

    std::cout<<"2NNN"<<std::endl;
    setSP(getSP()+1);
    memory->setStack(getSP(), getPC());
    setPC(_12LSb);
}

void CPU::_3(uint16_t _12LSb, Display *display, Memory *memory){

    std::cout<<"3XKK"<<std::endl;
    if(getRegister((_12LSb & 0x0F00) >> 8)==(_12LSb & 0x00FF)){
        setPC(getPC()+4);
        return;
    }
    setPC(getPC()+2);
}

void CPU::_4(uint16_t _12LSb, Display *display, Memory *memory){

    std::cout<<"4XKK"<<std::endl;
    if(getRegister((_12LSb & 0x0F00) >> 8)!=(_12LSb & 0x00FF)){
        setPC(getPC()+4);
        return;
    }
    setPC(getPC()+2);
}

void CPU::_5(uint16_t _12LSb, Display *display, Memory *memory){

    std::cout<<"5XY0"<<std::endl;
    if(getRegister((_12LSb & 0x0F00) >> 8)==getRegister((_12LSb & 0x00F0) >> 4)){
        setPC(getPC()+4);
        return;
    }
    setPC(getPC()+2);
}

void CPU::_6(uint16_t _12LSb, Display *display, Memory *memory){

    std::cout<<"6XKK"<<_12LSb<<std::endl;
    setRegister((_12LSb & 0x0F00)>>8, _12LSb & 0x00FF);
    setPC(getPC()+2);
}

void CPU::_7(uint16_t _12LSb, Display *display, Memory *memory){

    std::cout<<"7XKK"<<_12LSb<<std::endl;
    setRegister((_12LSb & 0x0F00)>>8, getRegister((_12LSb & 0x0F00)>>8)+(_12LSb & 0x00FF));
    setPC(getPC()+2);
}

void CPU::_8(uint16_t _12LSb, Display *display, Memory *memory){ 

    switch(_12LSb & 0x000F){
        case 0:
            std::cout<<"8XYO"<<std::endl;
            setRegister((_12LSb & 0x0F00) >> 8, getRegister((_12LSb & 0x00F0) >> 4));
            break;

        case 1:
            std::cout<<"8XY1"<<std::endl;
            setRegister((_12LSb & 0x0F00) >> 8, getRegister((_12LSb & 0x0F00) >> 8) | getRegister((_12LSb & 0x00F0) >> 4));
            break;

        case 2:
            std::cout<<"8XY2"<<std::endl;
            setRegister((_12LSb & 0x0F00) >> 8, getRegister((_12LSb & 0x0F00) >> 8) & getRegister((_12LSb & 0x00F0) >> 4));
            break;

        case 3:
            std::cout<<"8XY3"<<std::endl;
            setRegister((_12LSb & 0x0F00) >> 8, getRegister((_12LSb & 0x0F00) >> 8) ^ getRegister((_12LSb & 0x00F0) >> 4));
            break;

        case 4:
            std::cout<<"8XY4"<<std::endl;
            setRegister(15, ((uint16_t)getRegister((_12LSb & 0x0F00) >> 8) + (uint16_t)getRegister((_12LSb & 0x00F0) >> 4))>255);
            setRegister((_12LSb & 0x0F00) >> 8, ((uint16_t)getRegister((_12LSb & 0x0F00) >> 8) + (uint16_t)getRegister((_12LSb & 0x00F0) >> 4)) & 0x00FF);
            break;

        case 5:
            std::cout<<"8XY5"<<std::endl;
            setRegister(15, getRegister((_12LSb & 0x0F00) >> 8) > getRegister((_12LSb & 0x00F0) >> 4));
            setRegister((_12LSb & 0x0F00) >> 8, getRegister((_12LSb & 0x0F00) >> 8) - getRegister((_12LSb & 0x00F0) >> 4));
            break;

        case 6:
            std::cout<<"8XY6"<<std::endl;
            setRegister(15, getRegister(15) & 0x1);
            setRegister((_12LSb & 0x0F00) >> 8, getRegister((_12LSb & 0x0F00) >> 8) >> 1);
            break;

        case 7:
            std::cout<<"8XY7"<<std::endl;
            setRegister(15, getRegister((_12LSb & 0x0F00) >> 8) < getRegister((_12LSb & 0x00F0) >> 4));
            setRegister((_12LSb & 0x0F00) >> 8, getRegister((_12LSb & 0x00F0) >> 4) - getRegister((_12LSb & 0x0F00) >> 8));
            break;

        case 14:
            std::cout<<"8XYE"<<std::endl;
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

    std::cout<<"9XY0"<<std::endl;
    if(getRegister((_12LSb & 0x0F00) >> 8)!=getRegister((_12LSb & 0x00F0) >> 4)){
        setPC(getPC()+4);
        return;
    }
    setPC(getPC()+2);
}

void CPU::_A(uint16_t _12LSb, Display *display, Memory *memory){

    std::cout<<"ANNN"<<_12LSb<<std::endl;
    setI(_12LSb);
    setPC(getPC()+2);
}

void CPU::_B(uint16_t _12LSb, Display *display, Memory *memory){

    std::cout<<"BNNN"<<std::endl;
    setPC(_12LSb + getRegister(0));
}

void CPU::_C(uint16_t _12LSb, Display *display, Memory *memory){

    std::cout<<"CXKK"<<std::endl;
    setRegister((_12LSb & 0x0F00) >> 8, (rand() % 256) & (_12LSb & 0x00FF));
    setPC(getPC()+2);
}

void CPU::_D(uint16_t _12LSb, Display *display, Memory *memory){

    //DISPLAY
    std::cout<<"DXYN"<<std::endl;
    uint8_t sprite;
    V[15]=0;
    for(int i=0; i<_12LSb & 0x000F; i++){
        sprite=memory->getMemory(i+getI());
        if(((display->getGraphicsBuffer(((_12LSb & 0x0F00) >>8) + (((_12LSb & 0x00F0) >>4)))) ^ sprite) | ((display->getGraphicsBuffer(((_12LSb & 0x0F00) >>8) + (((_12LSb & 0x00F0) >>4)))) ^ 0xFF) !=0xFF){
            V[15]=1;
        }
        display->setGraphicsBuffer(((_12LSb & 0x0F00) >>8) + (((_12LSb & 0x00F0) >>4)), ((display->getGraphicsBuffer(((_12LSb & 0x0F00) >>8) + (((_12LSb & 0x00F0) >>4)))) ^ sprite));
    }
    setPC(getPC()+2);
}

void CPU::_E(uint16_t _12LSb, Display *display, Memory *memory){

    //KEYBOARD
    std::cout<<"E"<<std::endl;
    setPC(getPC()+2);
}

void CPU::_F(uint16_t _12LSb, Display *display, Memory *memory){

    switch(_12LSb & 0x00FF){

        case 0x07:
            std::cout<<"FX07"<<std::endl;
            setRegister((_12LSb & 0x0F00)>>8, delay_timer);
            break;

        case 0x0A:
            std::cout<<"FX0A"<<std::endl;
            //KEYBOARD
            break;
        
        case 0x15:
            std::cout<<"FX15"<<std::endl;
            setDelayTimer(getRegister((_12LSb & 0x0F00)>>8));
            break;
        
        case 0x18:
            std::cout<<"FX18"<<std::endl;
            setSoundTimer(getRegister((_12LSb & 0x0F00)>>8));
            break;

        case 0x1E:
            std::cout<<"FX1E"<<std::endl;
            setI(getI()+getRegister((_12LSb & 0x0F00)>>8));
            break;

        case 0x29: 
            std::cout<<"FX29"<<std::endl;
            //DISPLAY
            break;

        case 0x33:
            std::cout<<"FX33"<<std::endl;
            //DUNNO
            break;

        case 0x55:
            std::cout<<"FX55"<<std::endl;
            for(int i=0; i<((_12LSb & 0x0F00)>>8); i++){
                memory->setMemory(getI()+i, getRegister(i));
            }
            break;

        case 0x65:
            std::cout<<"FX65"<<std::endl;
            for(int i=0; i<((_12LSb & 0x0F00)>>8); i++){
                setRegister(i, memory->getMemory(getI()+i));
            }
            break;
    }
    setPC(getPC()+2);
}