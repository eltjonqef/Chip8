all:
	g++ src/main.cpp src/chip8.cpp src/cpu.cpp src/display.cpp src/memory.cpp -w -lSDL2 -o chip8

clear:
	rm chip8
