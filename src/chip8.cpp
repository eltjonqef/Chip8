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
        memory->memory[0x200+i]= buffer[i];
    }
    bool isRunning=true;

    SDL_Event event;
    uint8_t KEYMAP[16] = {
    SDLK_x, // 0
    SDLK_1, // 1
    SDLK_2, // 2
    SDLK_3, // 3
    SDLK_q, // 4
    SDLK_w, // 5
    SDLK_e, // 6
    SDLK_a, // 7
    SDLK_s, // 8
    SDLK_d, // 9
    SDLK_z, // A
    SDLK_c, // B
    SDLK_4, // C
    SDLK_r, // D
    SDLK_f, // E
    SDLK_v  // F
};
    uint32_t pixels[2048];
    while(isRunning){
        SDL_PollEvent(&event);
        switch(event.type){
            case SDL_QUIT:
                isRunning=false;
                break;
            case SDL_KEYDOWN:
                for(int i=0; i<16; i++){
                    if(event.key.keysym.sym==KEYMAP[i]){
                        keyboard->keyboard[i]=1;
                    }
                }
                break;
            case SDL_KEYUP:
                for(int i=0; i<16; i++){
                    if(event.key.keysym.sym==KEYMAP[i]){
                        keyboard->keyboard[i]=0;
                    }
                }
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
            SDL_UpdateTexture(display->texture, NULL, pixels, 64 * sizeof(Uint32));
            SDL_RenderClear(display->renderer);
            SDL_RenderCopy(display->renderer, display->texture, NULL, NULL);
            SDL_RenderPresent(display->renderer);
        }
        SDL_Delay(32);
        //std::this_thread::sleep_for(std::chrono::milliseconds(120));
    }
}

void Chip8::Cycle(){

    uint16_t opcode = memory->memory[cpu->pc]<< 8 | memory->memory[cpu->pc+1];
    cpu->executeOpcode(opcode, display, memory, keyboard);
    if(cpu->delay_timer>0){
        cpu->delay_timer--;
    }
}