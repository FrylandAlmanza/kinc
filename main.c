/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard math, and strings
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdbool.h>
#include <emscripten.h>

#include "entity.h"
#include "sprites.h"

//Screen dimension constants
const int SCREEN_WIDTH = 512;
const int SCREEN_HEIGHT = 480;

SDL_Rect sprites[8];

struct context
{
    SDL_Renderer *renderer;
    SDL_Texture *spritesheet;
    Entity player;
    Entity tiles[240];
    bool up;
    bool down;
    bool left;
    bool right;
};

int loadSpritesheet(struct context *ctx)
{
    SDL_Surface *image = IMG_Load("assets/spritesheet.png");
    if (!image)
    {
        printf("IMG_Load: %s\n", IMG_GetError());
        return 0;
    }
    SDL_SetColorKey(image, SDL_TRUE, SDL_MapRGB(image->format, 0, 0xFF, 0xFF ));
    ctx->spritesheet = SDL_CreateTextureFromSurface(ctx->renderer, image);

    SDL_FreeSurface(image);

    return 1;
}

bool collides(Entity e1, Entity e2) {
    int aa = e1.r.x;
    int ab = e1.r.x + e1.r.w;
    int ac = e1.r.y;
    int ad = e1.r.y + e1.r.h;

    int ba = e2.r.x;
    int bb = e2.r.x + e2.r.w;
    int bc = e2.r.y;
    int bd = e2.r.y + e2.r.h;
    
    if (ab > ba && aa < bb && ad > bc && ac < bd) {
        return true;
    }
    return false;
}

bool entityCollision(Entity e, struct context *ctx) {
    for (int y = 0; y < 15; y++) {
        for (int x = 0; x < 16; x++) {
            if (!ctx->tiles[(y * 16) + x].solid) continue;
            if (collides(e, ctx->tiles[(y * 16) + x])) {
                return true;
            }
        }
    }
    return false;
}

void loop_handler(void *arg)
{
    struct context *ctx = arg;
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        switch (event.key.keysym.sym)
        {
            case SDLK_UP:
                if (event.key.type == SDL_KEYDOWN)
                    ctx->up = true;
                else if (event.key.type == SDL_KEYUP)
                    ctx->up = false;
                break;
            case SDLK_DOWN:
                if (event.key.type == SDL_KEYDOWN)
                    ctx->down = true;
                else if (event.key.type == SDL_KEYUP)
                    ctx->down = false;
                break;
            case SDLK_LEFT:
                if (event.key.type == SDL_KEYDOWN)
                    ctx->left = true;
                else if (event.key.type == SDL_KEYUP)
                    ctx->left = false;
                break;
            case SDLK_RIGHT:
                if (event.key.type == SDL_KEYDOWN)
                    ctx->right = true;
                else if (event.key.type == SDL_KEYUP)
                    ctx->right = false;
                break;
            default:
                break;
        }
    }

    ctx->player.vx = 0;
    ctx->player.vy = 0;
    if (ctx->up) {
        ctx->player.vy = -1;
    }
    if (ctx->right) {
        ctx->player.vx = 1;
    }
    if (ctx->down) {
        ctx->player.vy = 1;
    }
    if (ctx->left) {
        ctx->player.vx = -1;
    }

    ctx->player.r.x += ctx->player.vx;
    ctx->player.r.y += ctx->player.vy;

    if (entityCollision(ctx->player, ctx)) {
        bool resolved = false;
        ctx->player.r.x -= ctx->player.vx;
        if (entityCollision(ctx->player, ctx)) {
            ctx->player.r.x += ctx->player.vx;
        } else {
            resolved = true;
        }
        if (!resolved) {
            ctx->player.r.y -= ctx->player.vy;
            if (entityCollision(ctx->player, ctx)) {
                ctx->player.r.y += ctx->player.vy;
            } else {
                resolved = true;
            }
        }
        if (!resolved) {
            ctx->player.r.x -= ctx->player.vx;
            ctx->player.r.y -= ctx->player.vy;
        }
    }

    SDL_RenderClear(ctx->renderer);
    for (int y = 0; y < 15; y++) {
        for (int x = 0; x < 16; x++) {
            int i = (y * 16) + x;
            SDL_RenderCopy(ctx->renderer, ctx->spritesheet, &sprites[ctx->tiles[i].sprite], &ctx->tiles[i].r);
        }
    }
    SDL_RenderCopy(ctx->renderer, ctx->spritesheet, &sprites[ctx->player.sprite], &ctx->player.r);
    SDL_RenderPresent(ctx->renderer);
}

void setSprites()
{
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



int main(int argc, char* args[])
{
    SDL_Window *window;
    struct context ctx;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &window, &ctx.renderer);
    SDL_SetRenderDrawColor(ctx.renderer, 0, 0, 0, 0);

    loadSpritesheet(&ctx);
    setSprites();
    
    //Main loop flag
    //ctx->quit = false;
    ctx.up = false;
    ctx.right = false;
    ctx.down = false;
    ctx.left = false;
    ctx.player.r.x = 64;
    ctx.player.r.y = 64;
    ctx.player.r.w = 16;
    ctx.player.r.h = 16;
    Entity tempTile;
    tempTile.r.w = 16;
    tempTile.r.h = 16;
    char *overworld = ""
"#######..#######"
"#### #'..#######"
"###'.....#######"
"##'......#######"
"#'.......`######"
"................"
"#!.............#"
"##.............#"
"##.............#"
"################"
"                "
" . . . .  . ... "
" ..  . .. .   . "
" . . . . ..  .  "
" . . . .  . ... ";
    int cursor;
    char tileChar;
    for (int y = 0; y < 15; y++) {
        for (int x = 0; x < 16; x++) {
            cursor = (y * 16) + x;
            tileChar = overworld[cursor];
            tempTile.r.x = x * 16;
            tempTile.r.y = y * 16;
            tempTile.solid = true;
            if (tileChar == '/') {
                tempTile.sprite = sprWallNW;
            } else if (tileChar == '-') {
                tempTile.sprite = sprWallN;
            } else if (tileChar == '!') {
                tempTile.sprite = sprWallNE;
            } else if (tileChar == '`') {
                tempTile.sprite = sprWallSW;
            } else if (tileChar == '#') {
                tempTile.sprite = sprWallS;
            } else if (tileChar == '\'') {
                tempTile.sprite = sprWallSE;
            } else if (tileChar == '.') {
                tempTile.sprite = sprGround;
                tempTile.solid = false;
            } else {
                tempTile.sprite = sprWallS;
            }
            ctx.tiles[(y * 16) + x] = tempTile;
        }
    }

    emscripten_set_main_loop_arg(loop_handler, &ctx, -1, 1);
    /*while (1) {
        loop_handler(&ctx);
        usleep(16666);
    }*/

    return 0;
}
