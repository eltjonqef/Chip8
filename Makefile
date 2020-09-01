all:
	g++ -g src/main.cpp src/chip8.cpp src/cpu.cpp src/display.cpp src/memory.cpp -o chip8 -I/usr/include/allegro5 -L/usr/lib -lallegro

clear:
	rm chip8
