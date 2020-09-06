#include "display.hpp"

Display::Display(){
    ClearDisplay();
}

void Display::ClearDisplay(){
    memset(graphics_buffer, 0, sizeof(graphics_buffer));
}

uint8_t Display::getFont(int i){
    return fonts[i];
}

uint8_t Display::getGraphicsBuffer(int i){
    return graphics_buffer[i];
}

void Display::setGraphicsBuffer(int index, uint8_t value){
    graphics_buffer[index]=value;
}