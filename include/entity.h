#ifndef ENTITY_H
#define ENTITY_H

#include <raylib.h>

#include "timer.h"
#include "sprite.h"



typedef struct _petTimer{
    void* pet;
    int currentTime;
    int maxTime;
    bool started;
    bool repeat;
    void (*callBack)(void*);
} PetTimer;



typedef struct _entity{
    Vector2 position;
    Vector2 velocity;
    Sprite sprite;
} Entity;

typedef enum _direction{
    UP,
    RIGHT,
    DOWN,
    LEFT
} Direction;

typedef struct _pet {
    Entity entity;
    Direction direction;
    PetTimer petTimer;
} Pet;

typedef struct _button{
    Entity entity;
    Rectangle collider;
    void (*onClickButton)(void*);
} Button;

void Entity_init(Entity*,char*, Vector2,Vector2);
void Entity_update(Entity*);
void Entity_draw(Entity*);
void Entity_unload(Entity*);


//pet functions

void Pet_Init(Pet*, char*, Vector2);
void Pet_update(Pet*);
void Pet_draw(Pet*);

void PetTimer_init(PetTimer* timer,Pet* pet, int maxTime, bool started, bool repeat,void (*callBack)(void*));
void PetTimer_start(PetTimer* timer);
void PetTimer_stop(PetTimer* timer);
void PetTimer_pause(PetTimer* timer);
void PetTimer_update(PetTimer* timer);

//Button Functions

void Button_init(Button* button, char* fileName, Vector2 position, void (*onClickButton)(void* button));
void Button_update(Button* button);
void Button_draw(Button* button);
void Button_unload(Button* button);
#endif // ENTITY_H

