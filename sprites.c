#include "sprites.h"

int framec;
int frame;

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
