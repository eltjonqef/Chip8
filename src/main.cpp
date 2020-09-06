#include "chip8.hpp"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
int main(){

    Chip8 *chip8 = new Chip8("test_opcode.ch8");
    if (!al_init()) {
		std::cout<<"failed to create display!"<<std::endl;
		exit(-1);
	}
    ALLEGRO_DISPLAY *display=al_create_display(1100, 700);
    al_init_primitives_addon();
        //al_draw_filled_rectangle(50, 50, 50+50, 50+50, al_map_rgb(255,255,255));
        while(1){
            for(int i=0; i<64; i++){
            for(int j=0; j<32; j++){
                if(chip8->getDisplay().getGraphicsBuffer(i+j)==1)
                    al_draw_filled_rectangle(i*15, j*15, i*15+15, j*15+15, al_map_rgb(255,255,255));
            }
        }
            al_flip_display();
        }
    al_rest(5);
    al_destroy_display(display);
    return 0;
}