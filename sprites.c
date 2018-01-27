#include "sprites.h"
#include "lua.vm.js/lua/src/lua.h"
#include "lua.vm.js/lua/src/lauxlib.h"
#include "lua.vm.js/lua/src/lualib.h"

int framec;
int frame;

void setSprites()
{
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);

    luaL_loadfile(L, "assets/sprites.lua");
    lua_pcall(L, 0, 0, 0);
        /*error(L, "cannot run configuration file: %s",
                lua_tostring(L, -1));*/
    lua_getglobal(L, "sprite_count");
    int sprite_count = (int)lua_tonumber(L, -1);
    sprites = malloc(sprite_count * sizeof(SDL_Rect));
    printf("sprite count: %d\n", sprite_count);
    lua_pop(L, 1);
    lua_getglobal(L, "sprites");
    for (int i = 0; i < sprite_count; i++) {
        lua_pushnumber(L, i);
        lua_gettable(L, -2);
        lua_pushstring(L, "x");
        lua_gettable(L, -2);
        sprites[i].x = (int)lua_tonumber(L, -1);
        lua_pop(L, 1);
        lua_pushstring(L, "y");
        lua_gettable(L, -2);
        sprites[i].y = (int)lua_tonumber(L, -1);
        lua_pop(L, 1);
        lua_pushstring(L, "w");
        lua_gettable(L, -2);
        sprites[i].w = (int)lua_tonumber(L, -1);
        lua_pop(L, 1);
        lua_pushstring(L, "h");
        lua_gettable(L, -2);
        sprites[i].h = (int)lua_tonumber(L, -1);
        lua_pop(L, 1);
        lua_pop(L, 1);
        printf("%d, %d, %d, %d\n", sprites[i].x, sprites[i].y, sprites[i].w, sprites[i].h);
    }
    lua_pop(L, 1);

    lua_close(L);
}

void setAnimations() {
    // Link walking down
    animations[0].frames = malloc(2 * sizeof(enum sprite));
    animations[0].frames[0] = sprKink;
    animations[0].frames[1] = sprWallS;
    animations[0].frame_time = 30;
    animations[0].frame_count = 2;
    animations[0].current_frame = 0;
    animations[0].time_since_last_frame = 0;
}

void freeAnimations() {
    free(animations[0].frames);
}

void advanceAnimation(struct animation *animation) {
    animation->time_since_last_frame++;
    if (animation->time_since_last_frame == animation->frame_time) {
        animation->time_since_last_frame = 0;
        animation->current_frame++;
        if (animation->current_frame == animation->frame_count) {
            animation->current_frame = 0;
        }
    }
}

SDL_Rect *getAnimationSprite(struct animation *animation) {
    framec = animation->frame_count;
    frame = animation->current_frame;
    return &sprites[animation->frames[animation->current_frame]];
}
