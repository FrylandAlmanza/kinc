#ifndef ENTITY_H_
#define ENTITY_H_

#include <SDL.h>
#include "sprites.h"

typedef struct entity_struct Entity;

struct entity_struct {
    SDL_Rect r;
    int vx;
    int vy;
    bool solid;
    enum sprite sprite;
    struct animation animation;
};

#endif
