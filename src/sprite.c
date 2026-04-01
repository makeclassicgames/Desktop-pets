#include "sprite.h"

void Sprite_init(Sprite* sprite,char * fileName){

    sprite->texture = LoadTexture(fileName);
    sprite->currentAnimation =0;
    sprite->animationCount =0;
}

void Sprite_update(Sprite* sprite){
    Animation_Update(&sprite->animations[sprite->currentAnimation]);
}

void Sprite_draw(Sprite* sprite, int x, int y){
    Animation_Draw(&sprite->animations[sprite->currentAnimation],
         &sprite->texture, sprite->currentAnimation, x, y);
}

void Sprite_Unload(Sprite* sprite){
    UnloadTexture(sprite->texture);
}

void Sprite_setAnimation(Sprite* sprite, int animationIndex){
    sprite->currentAnimation = animationIndex;
}

void Sprite_addAnimation(Sprite* sprite, int frameWidth, int frameHeight, int frameCount, int frameDelay){
    if(sprite->animationCount>=MAX_ANIMS){
        TraceLog(LOG_ERROR,"Max Animations Reached");
        return;
    }

    Animation_Init(&sprite->animations[sprite->animationCount],frameWidth,frameHeight,frameCount,frameDelay);
    sprite->animationCount++;
}

//Animation Functions

void Animation_Init(Animation * animation, int frameWidth, int frameHeight, int frameCount, int frameDelay){
    animation->currentFrame=0;
    animation->frameCount=frameCount;
    animation->frameWidth = frameWidth;
    animation->frameHeight = frameHeight;
    animation->frameDelay = frameDelay;
    animation->current_time = 0;
}

void Animation_Update(Animation * animation){
    animation->current_time++;
    if(animation->current_time >= animation->frameDelay){
        animation->currentFrame++;
        if(animation->currentFrame>=animation->frameCount){
            animation->currentFrame = 0;
        }
        animation->current_time = 0;
    }

}

void Animation_Draw(Animation * animation, Texture2D* texture,int animationRow, int x, int y){
    Rectangle frameRec = {animation->currentFrame*texture->width/animation->frameCount,animationRow*animation->frameHeight, animation->frameWidth,animation->frameHeight};
    Rectangle destRec = {x,y,animation->frameWidth*2,animation->frameHeight*2};
    Vector2 origin = {0,0};
    DrawTexturePro(*texture,frameRec,destRec,origin,0.0f,WHITE);
    
}