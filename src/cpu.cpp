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

void CPU::executeOpcode(uint16_t opcode, Display *display, Memory *memory, Keyboard *keyboard){
    (this->*opcodes[(opcode & 0xF000) >>12])(opcode & 0x0FFF, display, memory, keyboard);
}

void CPU::_0(uint16_t _12LSb, Display *display, Memory *memory, Keyboard *keyboard){

    switch(_12LSb){
        case 0x0E0:
            display->ClearDisplay();
            pc+=2;
            break;

        case 0x0EE:
            sp--;
            pc=memory->stack[sp];          
            break;
        
        default:
            std::cout<<"Unknown Instruction 00EX"<<std::endl;
            exit(EXIT_FAILURE);
            break;
    }
}

void CPU::_1(uint16_t _12LSb, Display *display, Memory *memory, Keyboard *keyboard){

    pc=_12LSb;
}

void CPU::_2(uint16_t _12LSb, Display *display, Memory *memory, Keyboard *keyboard){

    memory->stack[sp]=pc;
    sp++;    
    pc=_12LSb;
}

void CPU::_3(uint16_t _12LSb, Display *display, Memory *memory, Keyboard *keyboard){

    uint8_t x=(_12LSb & 0x0F00) >> 8;
    uint8_t nn=_12LSb & 0x00FF;
    if(V[x]==nn){
        pc+=4;
        return;
    }
    pc+=2;
}

void CPU::_4(uint16_t _12LSb, Display *display, Memory *memory, Keyboard *keyboard){

    uint8_t x=(_12LSb & 0x0F00) >> 8;
    uint8_t nn=_12LSb & 0x00FF;
    if(V[x]!=nn){
        pc+=4;
        return;
    }
    pc+=2;
}

void CPU::_5(uint16_t _12LSb, Display *display, Memory *memory, Keyboard *keyboard){

    uint8_t x=(_12LSb & 0x0F00) >> 8;
    uint8_t y=(_12LSb & 0x00F0) >> 4;
    if(V[x]==V[y]){
        pc+=4;
        return;
    }
    pc+=2;
}

void CPU::_6(uint16_t _12LSb, Display *display, Memory *memory, Keyboard *keyboard){

    uint8_t x=(_12LSb & 0x0F00) >> 8;
    uint8_t nn=_12LSb & 0x00FF;
    V[x]= nn;
    pc+=2;
}

void CPU::_7(uint16_t _12LSb, Display *display, Memory *memory, Keyboard *keyboard){

    uint8_t x=(_12LSb & 0x0F00) >> 8;
    uint8_t nn=_12LSb & 0x00FF;
    V[x]+=nn;
    pc+=2;
}

void CPU::_8(uint16_t _12LSb, Display *display, Memory *memory, Keyboard *keyboard){ 

    uint8_t x=(_12LSb & 0x0F00) >> 8;
    uint8_t y=(_12LSb & 0x00F0) >> 4;
    switch(_12LSb & 0x000F){
        case 0:
            V[x]=V[y];
            break;

        case 1:
            V[x]|=V[y];
            break;

        case 2:
            V[x]&=V[y];
            break;

        case 3:
            V[x]^=V[y];
            break;

        case 4:
            V[0xF]=(V[x] + V[y]) > 255;
            V[x]+=V[y];
            break;

        case 5:
            V[0xF]=V[x]>V[y];
            V[x]-=V[y];
            break;

        case 6:
            std::cout<<"8XY6"<<std::endl;
            V[0xF] &= 0x1;
            V[0xF] >>= 1;
            break;

        case 7:
            std::cout<<"8XY7"<<std::endl;
            V[0xF] = (V[x] < V[y]);
            V[x] = V[y] - V[x];
            break;

        case 14:
            std::cout<<"8XYE"<<std::endl;
            V[0xF]=V[x] & 0x80;
            V[x]= V[x] <<1;
            break;
        
        default: //Unknown Instruction
            std::cout<<"Unknown Instruction"<<std::endl;
            exit(EXIT_FAILURE);
            break;
    }
    pc+=2;
}

void CPU::_9(uint16_t _12LSb, Display *display, Memory *memory, Keyboard *keyboard){

    uint8_t x=(_12LSb & 0x0F00) >> 8;
    uint8_t y=(_12LSb & 0x00F0) >> 4;
    if(V[x]!=V[y]){
        pc+=4;
        return;
    }
    pc+=2;
}

void CPU::_A(uint16_t _12LSb, Display *display, Memory *memory, Keyboard *keyboard){

    i=_12LSb;
    pc+=2;
}

void CPU::_B(uint16_t _12LSb, Display *display, Memory *memory, Keyboard *keyboard){

    pc=_12LSb + V[0];
}

void CPU::_C(uint16_t _12LSb, Display *display, Memory *memory, Keyboard *keyboard){

    uint8_t x=(_12LSb & 0x0F00) >> 8;
    uint8_t nn=_12LSb & 0x00FF;
    V[x]=(rand() % 256) & nn;
    pc+=2;
}

void CPU::_D(uint16_t _12LSb, Display *display, Memory *memory, Keyboard *keyboard){

    //DISPLAY
    std::cout<<"DXYN"<<std::endl;
    uint8_t sprite;
    display->draw=true;
    V[0xF]=0;
    for(int yline=0; yline<(_12LSb & 0x00F); yline++){
        sprite=memory->memory[i + yline];
        for(int xline=0; xline<8; xline++){
            if((sprite & (0x80 >> xline)) !=0){
                if(display->graphics_buffer[V[((_12LSb & 0xF00)>> 8)+xline+(((_12LSb & 0x0F0)>> 4) +yline)*64]]==1){
                    V[0xF]=1;
                }
                display->graphics_buffer[((_12LSb & 0xF00)>> 8)+xline+(((_12LSb & 0x0F0)>> 4) +yline)*64] ^= 1;
            }
        }
    }
    /*
    for(int i=0; i<_12LSb & 0x000F; i++){
        sprite=memory->getMemory(i+getI());
        if(((display->getGraphicsBuffer(((_12LSb & 0x0F00) >>8) + (((_12LSb & 0x00F0) >>4)))) ^ sprite) | ((display->getGraphicsBuffer(((_12LSb & 0x0F00) >>8) + (((_12LSb & 0x00F0) >>4)))) ^ 0xFF) !=0xFF){
            V[15]=1;
        }
        display->setGraphicsBuffer(((_12LSb & 0x0F00) >>8) + (((_12LSb & 0x00F0) >>4)), ((display->getGraphicsBuffer(((_12LSb & 0x0F00) >>8) + (((_12LSb & 0x00F0) >>4)))) ^ sprite));
    }*/
    pc+=2;
}

void CPU::_E(uint16_t _12LSb, Display *display, Memory *memory, Keyboard *keyboard){

    //KEYBOARD
    uint8_t x=(_12LSb & 0x0F00) >> 8;
    switch(_12LSb & 0x00FF){
        case 0x9E:
            if(keyboard->keys[x]){
                pc+=4;
                return;
            }
            break;
        
        case 0xA1:
            if(!keyboard->keys[x]){
                pc+=4;
                return;
            }
            break;
        default:
            std::cout<<"ERROR"<<std::endl;
            exit(EXIT_FAILURE);
    }
    pc+=2;
}

void CPU::_F(uint16_t _12LSb, Display *display, Memory *memory, Keyboard *keyboard){

    uint8_t x=(_12LSb & 0x0F00)>>8;
    std::cout<<"tetetetete "<<(_12LSb & 0x00FF)<<std::endl;
    switch(_12LSb & 0x00FF){

        case 0x07:
            V[x]=delay_timer;
            break;

        case 0x0A:
            //KEYBOARD
            break;
        
        case 0x15:
            delay_timer=V[x];
            break;
        
        case 0x18:
            sound_timer=V[x];
            break;

        case 0x1E:
            std::cout<<"FX1E"<<std::endl;
            i+=V[x];
            break;

        case 0x29: 
            i=V[x];
            break;

        case 0x33:
            memory->memory[i]=V[x/100] /100;
            memory->memory[i]=(V[x] /10) % 10;
            memory->memory[i]=V[x] % 10;
            break;

        case 0x55:
            for(int j=0; j<=((_12LSb & 0x0F00)>>8); j++){
                memory->memory[i+j]=V[j];
            }
            break;

        case 0x65:
            for(int j=0; j<=((_12LSb & 0x0F00)>>8); j++){
                V[j]=memory->memory[i+j];
            }
            break;
        default:
            std::cout<<"ERROR"<<std::endl;
            exit(EXIT_FAILURE);
    }
    pc+=2;
}