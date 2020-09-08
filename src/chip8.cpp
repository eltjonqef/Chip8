#include "chip8.hpp"


Chip8::Chip8(std::string filename){

    display= new Display();
    memory= new Memory();
    cpu= new CPU();
    keyboard = new Keyboard();
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
    bool isRunning=true;
    SDL_Event event;
    while(isRunning){
        SDL_PollEvent(&event);
        switch(event.type){
            case SDL_QUIT:
                isRunning=false;
                break;
            case SDL_KEYUP:
                break;
            case SDL_KEYDOWN:
                std::cout<<event.key.keysym.sym<<std::endl;
                keyboard->setKey(event.key.keysym.sym);
                break;
            default:
                break;
        }
        //Cycle();
        SDL_RenderClear(display->getRenderer());
        SDL_RenderPresent(display->getRenderer());
    }
}

void Chip8::Cycle(){

    uint16_t opcode= memory->getMemory(cpu->getPC()) << 8 | memory->getMemory(cpu->getPC()+1);
    cpu->executeOpcode(opcode, display, memory, keyboard);
}


Display& Chip8::getDisplay(){
    return *display;
}

Keyboard& Chip8::getKeyboard(){
    return *keyboard;
}