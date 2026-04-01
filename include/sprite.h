#pragma once

#include <raylib.h>

#define MAX_ANIMS 4

typedef struct _animation{
    int frameWidth;
    int frameHeight;
    int frameCount;
    int currentFrame;
    int current_time;
    int frameDelay;
} Animation;

typedef struct _sprite{
    Texture2D texture;
    Animation animations[MAX_ANIMS];
    int currentAnimation;
    int animationCount;
} Sprite;

void Sprite_init(Sprite*, char *);
void Sprite_update(Sprite*);
void Sprite_draw(Sprite*, int, int );
void Sprite_Unload(Sprite*);
void Sprite_setAnimation(Sprite*, int );
void Sprite_addAnimation(Sprite*, int , int , int , int );
//Animation

void Animation_Init(Animation * animation, int frameWidth, int frameHeight, int frameCount, int frameDelay);
void Animation_Update(Animation * animation);
void Animation_Draw(Animation * animation, Texture2D* texture,int animationRow, int x, int y);