#include "chip8.hpp"
#include <SDL2/SDL.h>

bool init();
void destroy();
SDL_Window *window=NULL;
SDL_Renderer *renderer=NULL;
int main(){

    Chip8 *chip8 = new Chip8("Brix [Andreas Gustafsson, 1990].ch8");

    return 0;
}

