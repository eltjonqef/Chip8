all:
	g++ main.cpp chip8.cpp cpu.cpp display.cpp memory.cpp -w -lSDL2 -o chip8

clear:
	rm chip8
