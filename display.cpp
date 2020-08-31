#include "display.hpp"

Display::Display(){
    memset(graphics_buffer, 0, sizeof(graphics_buffer));
}

uint8_t Display::getFont(int i){
    return fonts[i];
}