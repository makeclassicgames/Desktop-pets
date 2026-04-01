#include "entity.h"

#define PET_SPEED 100

void onPetTimer(void*);

void Entity_init(Entity* entity,char* fileName, Vector2 position,Vector2 velocity){
    entity->position = position;
    entity->velocity = velocity;
    Sprite_init(&entity->sprite,fileName);
}

void Entity_update(Entity* entity){
    float dt = GetFrameTime();
    entity->position.x += entity->velocity.x*dt;
    entity->position.y += entity->velocity.y*dt;
    Sprite_update(&entity->sprite); 
}

void Entity_draw(Entity* entity){
    Sprite_draw(&entity->sprite,entity->position.x,entity->position.y);
}

void Entity_unload(Entity* entity){
    Sprite_Unload(&entity->sprite);
}


void Pet_Init(Pet* pet, char* fileName, Vector2 position){
    Entity_init(&pet->entity,fileName,position,(Vector2){0.0,0.0});
    pet->direction = LEFT;
    PetTimer_init(&pet->petTimer,(void*)pet,5,true,true,onPetTimer);
}

void Pet_update(Pet* pet){

    if(pet->entity.position.x<=0){
        pet->entity.velocity.x= PET_SPEED;
        pet->direction= RIGHT;
    }
    if(pet->entity.position.x>=GetScreenWidth()- pet->entity.sprite.animations[pet->entity.sprite.currentAnimation].frameWidth){
        pet->entity.velocity.x= -PET_SPEED;
        pet->direction= LEFT;
    }
    PetTimer_update(&pet->petTimer);
    Sprite_setAnimation(&pet->entity.sprite,pet->direction);
    Entity_update(&pet->entity);
}

void Pet_draw(Pet* pet){
    Entity_draw(&pet->entity);
}

void onPetTimer(void* petRef){
    Pet* pet = (Pet*)petRef;
    int value = GetRandomValue(0,2);
    switch (value)
    {
    case 0:
        pet->entity.velocity.x= -PET_SPEED;
        pet->direction= LEFT;
        break;
    case 1:
        pet->entity.velocity.x= PET_SPEED;
        pet->direction= RIGHT;
        break;
    case 2:
        pet->entity.velocity.x= 0;
        pet->direction= DOWN;
        break;
    default:
        break;
    }
}


void PetTimer_init(PetTimer* timer,Pet* pet, int maxTime, bool autoStart, bool repeat,void (*callBack)(void*)){
    timer->callBack=callBack;
    timer->currentTime=0;
    timer->maxTime=SECONDS_TOFRAMES(maxTime);
    timer->started = autoStart;
    timer->repeat = repeat;
    timer->pet = pet;
}
void PetTimer_start(PetTimer* timer){
        timer->started = true;

}
void PetTimer_stop(PetTimer* timer){
    timer->started = false;
    timer->currentTime = 0;
}
void PetTimer_pause(PetTimer* timer){
    timer->started= false;
}
void PetTimer_update(PetTimer* timer){
      if(!timer->started) return;

    if(timer->currentTime>=timer->maxTime){
        timer->callBack(timer->pet);
        if(timer->repeat){
            timer->currentTime = 0;
        }else{
            timer->started = false;
        }
    }

    timer->currentTime ++;
}