#ifndef ENTITY_H_
#define ENTITY_H_

#include "sprites.h"

typedef struct entity_struct Entity;

struct entity_struct {
    int x;
    int y;
    int w;
    int h;
    int xSpeed;
    int ySpeed;
    bool solid;
    enum sprite sprite;
};

#endif
