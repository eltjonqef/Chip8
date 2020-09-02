#include "display.hpp"

Display::Display(){
    ClearDisplay();
    /*if (!al_init()) {
		std::cout<<"failed to create display!"<<std::endl;
		exit(-1);
	}
    display=al_create_display(600, 600);
    al_rest(10.0);
    al_destroy_display(display);*/
}

void Display::ClearDisplay(){
    memset(graphics_buffer, 0, sizeof(graphics_buffer));
}

uint8_t Display::getFont(int i){
    return fonts[i];
}