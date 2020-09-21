#include "display.hpp"

Display::Display(){
    ClearDisplay();
    window=NULL;
    renderer=NULL;
    texture=NULL;
    draw=false;
    initSDL();
}

Display::~Display(){
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

void Display::ClearDisplay(){
    memset(graphics_buffer, 0, sizeof(graphics_buffer));
}

bool Display::initSDL(){
    
    if(SDL_Init(SDL_INIT_EVERYTHING)!=0){
        std::cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
        return 0;
    }
    std::cout <<"Initialized SDL succesfully!" << std::endl;
    window=SDL_CreateWindow("Chip8", 0, 0, 1024, 500, SDL_WINDOW_SHOWN); 
    if(!window){
        std::cout << "SDL could not create window! SDL Error: " << SDL_GetError() << std::endl;
        return 0;
    }   
    std::cout <<"SDL created window succesfully!" << std::endl;
    renderer=SDL_CreateRenderer(window, -1, 0);
    if(!renderer){
        std::cout << "SDL could not create renderer! SDL Error: " << SDL_GetError() << std::endl;
        return 0;
    }
    std::cout <<"SDL created renderer succesfully!" << std::endl;
    SDL_RenderSetLogicalSize(renderer, 1024, 500);
    texture=SDL_CreateTexture(renderer,
                SDL_PIXELFORMAT_ARGB8888,
                SDL_TEXTUREACCESS_STREAMING,
                64, 32);
    return 1;
}