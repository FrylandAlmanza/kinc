/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

#include <time.h>

//Using SDL, SDL_image, standard math, and strings
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdbool.h>

#include "entity.h"
#include "sprites.h"

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

Entity tiles[240];

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
    SDL_RenderCopy(gRenderer, spritesheet, clip, &renderQuad);
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
    loadSheetFromFile("assets/spritesheet.png");

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

bool collides(Entity e1, Entity e2) {
    int aa = e1.x;
    int ab = e1.x + e1.w;
    int ac = e1.y;
    int ad = e1.y + e1.h;

    int ba = e2.x;
    int bb = e2.x + e2.w;
    int bc = e2.y;
    int bd = e2.y + e2.h;
    
    if (ab > ba && aa < bb && ad > bc && ac < bd) {
        return true;
    }
    return false;
}

bool entityCollision(Entity e) {
    for (int y = 0; y < 15; y++) {
        for (int x = 0; x < 16; x++) {
            if (!tiles[(y * 16) + x].solid) continue;
            if (collides(e, tiles[(y * 16) + x])) {
                return true;
            }
        }
    }
    return false;
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
    Entity player;
    player.x = 16;
    player.y = 16;
    player.w = 16;
    player.h = 16;
    Entity tempTile;
    tempTile.w = 16;
    tempTile.h = 16;
    for (int y = 0; y < 15; y++) {
        for (int x = 0; x < 16; x++) {
            tempTile.x = x * 16;
            tempTile.y = y * 16;
            tempTile.solid = true;
            if (x == 2 && y == 2) {
                tempTile.sprite = sprWallNW;
            } else if (x == 3 && y == 2) {
                tempTile.sprite = sprWallN;
            } else if (x == 4 && y == 2) {
                tempTile.sprite = sprWallNE;
            } else if (x == 2 && y == 3) {
                tempTile.sprite = sprWallSW;
            } else if (x == 3 && y == 3) {
                tempTile.sprite = sprWallS;
            } else if (x == 4 && y == 3) {
                tempTile.sprite = sprWallSE;
            } else if (x == 0 || y == 0 || x == 15 || y == 14) {
                tempTile.sprite = sprWallS;
            } else {
                tempTile.sprite = sprGround;
                tempTile.solid = false;
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

        player.xSpeed = 0;
        player.ySpeed = 0;
        if (up) {
            player.ySpeed = -1;
        }
        if (right) {
            player.xSpeed = 1;
        }
        if (down) {
            player.ySpeed = 1;
        }
        if (left) {
            player.xSpeed = -1;
        }

        player.x += player.xSpeed;
        player.y += player.ySpeed;

        if (entityCollision(player)) {
            bool resolved = false;
            player.x -= player.xSpeed;
            if (entityCollision(player)) {
                player.x += player.xSpeed;
            } else {
                resolved = true;
            }
            if (!resolved) {
                player.y -= player.ySpeed;
                if (entityCollision(player)) {
                    player.y += player.ySpeed;
                } else {
                    resolved = true;
                }
            }
            if (!resolved) {
                player.x -= player.xSpeed;
                player.y -= player.ySpeed;
            }
        }

        //Clear screen
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);

        for (int y = 0; y < 15; y++) {
            for (int x = 0; x < 16; x++) {
                int i = (y * 16) + x;
                renderSprite(tiles[i].x, tiles[i].y, &sprites[tiles[i].sprite]);
            }
        }

        //Render top left sprite
        renderSprite(player.x, player.y, &sprites[sprKink]);

        if (entityCollision(player)) {
            renderSprite(100, 100, &sprites[sprKink]);
        }

        //Update screen
        SDL_RenderPresent(gRenderer);


	    usleep(16666);
    }

    //Free resources and close SDL
    close();

    return 0;
}
