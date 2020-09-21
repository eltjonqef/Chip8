#include "chip8.hpp"


Chip8::Chip8(std::string filename){

    display= new Display();
    memory= new Memory();
    cpu= new CPU();
    keyboard = new Keyboard();
    for(int i=0; i<80; i++){
        memory->memory[i]=display->fonts[i];
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
        memory->memory[0x200+i, buffer[i]];
    }
    bool isRunning=true;
    SDL_RenderSetLogicalSize(display->renderer, 1024, 512);

        // Create texture that stores frame buffer
        SDL_Texture* sdlTexture = SDL_CreateTexture(display->renderer,
                SDL_PIXELFORMAT_ARGB8888,
                SDL_TEXTUREACCESS_STREAMING,
                64, 32);
    SDL_Event event;
    uint32_t pixels[2048];
    while(isRunning){
        SDL_PollEvent(&event);
        switch(event.type){
            case SDL_QUIT:
                isRunning=false;
                break;
            case SDL_KEYUP:
                keyboard->keys[event.key.keysym.sym]=0;
                break;
            case SDL_KEYDOWN:
                keyboard->keys[event.key.keysym.sym]=1;
                break;
            default:
                break;
        }
        Cycle();
        if(display->draw){
            display->draw=false;
            for(int i=0; i<2048; i++){
                uint8_t p=display->graphics_buffer[i];
                pixels[i]= (0x00FFFFFF * p) | 0xFF000000;
            }
            SDL_UpdateTexture(sdlTexture, NULL, pixels, 64 * sizeof(Uint32));
            // Clear screen and render
            SDL_RenderClear(display->renderer);
            SDL_RenderCopy(display->renderer, sdlTexture, NULL, NULL);
            SDL_RenderPresent(display->renderer);
        }
        //std::this_thread::sleep_for(std::chrono::milliseconds(120));
    }
}

void Chip8::Cycle(){

    uint16_t opcode = memory->memory[(cpu->pc << 8) | memory->memory[cpu->pc+1]];
    cpu->executeOpcode(opcode, display, memory, keyboard);
}