CC = gcc
default: main.c sprites.c
	$(CC) main.c sprites.c -o main -g -Wall -I/usr/include/SDL2 -lSDL2 -lSDL2_image -I lua/src -L lua/src -llua -ldl -lm

webbased: main.c sprites.c
	emcc main.c sprites.c -O2 -D WEBBASED -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='["png"]' -Ilua.vm.js/lua/src -Llua.vm.js/lua/src --embed-file assets -o main.html -llua -ldl -lm
