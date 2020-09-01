#include "chip8.hpp"
#include <SDL2/SDL.h>
#include <iostream>
#include <thread>
int main(){

    Chip8 chip8 = Chip8("Brix [Andreas Gustafsson, 1990].ch8");

    SDL_Window* window=SDL_CreateWindow("Chip8", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 500, 400, SDL_WINDOW_SHOWN);
    
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_RenderSetLogicalSize(renderer, 500, 400);

    SDL_Texture* sdlTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STREAMING, 64, 32);
    SDL_Event evt;
    bool programrunning = true;
    while(programrunning)
    {
    SDL_WaitEvent(&evt);
    if(evt.type == SDL_QUIT)
        programrunning = false;
    }
    return 0;
}