CC = gcc
default: main.c
	$(CC) main.c -o main -g -Wall -I/usr/include/SDL2 -lSDL2 -lSDL2_image

webbased: main.c
	emcc main.c -O2 -D WEBBASED -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='["png"]' --embed-file assets/spritesheet.png -o main.html
