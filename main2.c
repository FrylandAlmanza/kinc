/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

#include <time.h>

//Using SDL, SDL_image, standard math, and strings
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdbool.h>

struct player {
    int x;
    int y;
};

struct tile {
    int x;
    int y;
    SDL_Rect sprite;
};

//Screen dimension constants
const int SCREEN_WIDTH = 256;
const int SCREEN_HEIGHT = 240;

SDL_Texture* spritesheet;

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Scene sprites
SDL_Rect sprites[8];

void loadSheetFromFile(char path[256])
{
    SDL_Surface* loadedSurface = IMG_Load(path);
    SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF ));
    spritesheet = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
    SDL_FreeSurface(loadedSurface);
}

void freeSheet()
{
    SDL_DestroyTexture(spritesheet);
    spritesheet = NULL;
}

void renderSprite(int x, int y, SDL_Rect* clip)
{
    SDL_Rect renderQuad = {x, y, 16, 16};
    renderQuad.w = clip->w;
    renderQuad.h = clip->h;
    SDL_RenderCopy( gRenderer, spritesheet, clip, &renderQuad );
}

bool init()
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
    gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    int imgFlags = IMG_INIT_PNG;
    IMG_Init(imgFlags);
}

bool loadMedia()
{
    loadSheetFromFile("spritesheet.png");

    //link
    sprites[0].x = 0;
    sprites[0].y = 0;
    sprites[0].w = 16;
    sprites[0].h = 16;

    //tile1
    sprites[1].x = 32;
    sprites[1].y = 0;
    sprites[1].w = 16;
    sprites[1].h = 16;
    
    //tile2
    sprites[2].x = 48;
    sprites[2].y = 0;
    sprites[2].w = 16;
    sprites[2].h = 16;
    
    //tile3
    sprites[3].x = 64;
    sprites[3].y = 0;
    sprites[3].w = 16;
    sprites[3].h = 16;

    //tile4
    sprites[4].x = 32;
    sprites[4].y = 16;
    sprites[4].w = 16;
    sprites[4].h = 16;
    
    //tile5
    sprites[5].x = 48;
    sprites[5].y = 16;
    sprites[5].w = 16;
    sprites[5].h = 16;
    
    //tile6
    sprites[6].x = 64;
    sprites[6].y = 16;
    sprites[6].w = 16;
    sprites[6].h = 16;

    //tile7
    sprites[7].x = 32;
    sprites[7].y = 32;
    sprites[7].w = 16;
    sprites[7].h = 16;
}

void close()
{
    //Free loaded images
    freeSheet();

    //Destroy window	
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;

    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}

int main(int argc, char* args[])
{
    //Start up SDL and create window
    init();
    loadMedia();
    //Main loop flag
    bool quit = false;
    bool up = false;
    bool right = false;
    bool down = false;
    bool left = false;
    struct player player = {0, 0};
    struct tile tiles[240];
    struct tile tempTile;
    for (int y = 0; y < 15; y++) {
        for (int x = 0; x < 16; x++) {
            tempTile.x = x * 16;
            tempTile.y = y * 16;
            if (x == 2 && y == 2) {
                tempTile.sprite = sprites[1];
            } else if (x == 3 && y == 2) {
                tempTile.sprite = sprites[2];
            } else if (x == 4 && y == 2) {
                tempTile.sprite = sprites[3];
            } else if (x == 2 && y == 3) {
                tempTile.sprite = sprites[4];
            } else if (x == 3 && y == 3) {
                tempTile.sprite = sprites[5];
            } else if (x == 4 && y == 3) {
                tempTile.sprite = sprites[6];
            } else if (x == 0 || y == 0 || x == 15 || y == 14) {
                tempTile.sprite = sprites[5];
            } else {
                tempTile.sprite = sprites[7];
            }
            tiles[(y * 16) + x] = tempTile;
        }
    }

    //Event handler
    SDL_Event e;

    //While application is running
    while (!quit)
    {
        //Handle events on queue
        while (SDL_PollEvent(&e) != 0)
        {
            //User requests quit
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
            else if (e.type == SDL_KEYDOWN)
            {
                switch (e.key.keysym.sym)
                {
                    case SDLK_UP:
                        up = true;
                        break;
                    case SDLK_RIGHT:
                        right = true;
                        break;
                    case SDLK_DOWN:
                        down = true;
                        break;
                    case SDLK_LEFT:
                        left = true;
                        break;
                }
            }
            else if (e.type == SDL_KEYUP)
            {
                switch (e.key.keysym.sym) {
                    case SDLK_UP:
                        up = false;
                        break;
                    case SDLK_RIGHT:
                        right = false;
                        break;
                    case SDLK_DOWN:
                        down = false;
                        break;
                    case SDLK_LEFT:
                        left = false;
                        break;
                }
            }
        }

        if (up) {
            player.y -= 1;
        }
        if (right) {
            player.x += 1;
        }
        if (down) {
            player.y += 1;
        }
        if (left) {
            player.x -= 1;
        }

        //Clear screen
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);

        for (int y = 0; y < 15; y++) {
            for (int x = 0; x < 16; x++) {
                int i = (y * 16) + x;
                renderSprite(tiles[i].x, tiles[i].y, &tiles[i].sprite);
            }
        }

        //Render top left sprite
        renderSprite(player.x, player.y, &sprites[0]);

        //Update screen
        SDL_RenderPresent(gRenderer);

	usleep(16666);
    }

    //Free resources and close SDL
    close();

    return 0;
}
