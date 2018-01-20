CC = emcc
all: main.c
	$(CC) main.c -O2 -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='["png"]' --embed-file assets/spritesheet.png -o main.html
