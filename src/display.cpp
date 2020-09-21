#include "display.hpp"

Display::Display(){
    ClearDisplay();
    window=NULL;
    renderer=NULL;
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
    window=SDL_CreateWindow("Chip8", 0, 0, 500, 400, SDL_WINDOW_SHOWN); 
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
    return 1;
}