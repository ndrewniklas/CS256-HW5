all: main.cpp; clang++ -Wall -std=c++11 -o Gravity main.cpp Game.cpp Particle.cpp Point.cpp `pkg-config --cflags sdl2` `pkg-config --libs sdl2` -lSDL2_ttf 
