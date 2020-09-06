all:
	g++ -g src/main.cpp src/chip8.cpp src/cpu.cpp src/display.cpp src/memory.cpp -o chip8 -lallegro_ttf -lallegro_font -lallegro_primitives -lallegro_memfile -lallegro

clear:
	rm chip8
