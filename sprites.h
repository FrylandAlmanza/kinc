#ifndef SPRITES_H_
#define SPRITES_H_

#include <SDL.h>

SDL_Rect sprites[8];

enum sprite {
    sprKink,
    sprWallNW,
    sprWallN,
    sprWallNE,
    sprWallSW,
    sprWallS,
    sprWallSE,
    sprGround
};

struct animation {
    enum sprite *frames;
    int frame_count;
    int frame_time;
    int current_frame;
    int time_since_last_frame;
} animations[1];

void setSprites();
void setAnimations();
void freeAnimations();
void advanceAnimation(struct animation *animation);
SDL_Rect *getAnimationSprite(struct animation *animation);
#endif
