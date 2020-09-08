all:
	g++ -g src/main.cpp src/chip8.cpp src/cpu.cpp src/display.cpp src/memory.cpp -o chip8 -lSDL2

clear:
	rm chip8
