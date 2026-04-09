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
    for(int i =0; i<MAX_ANIMS;i++){
        Sprite_addAnimation(&pet->entity.sprite,32,32,3,15);
    }
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

void Button_init(Button* button, char* fileName, Vector2 position, void (*onClickButton)(void*)){
    Entity_init(&button->entity,fileName,position,(Vector2){0.0,0.0});
    Sprite_addAnimation(&button->entity.sprite,16,16,1,1);
    Animation * currentAnim = &button->entity.sprite.animations[button->entity.sprite.currentAnimation];
    button->collider = (Rectangle){position.x,position.y,currentAnim->frameWidth*2,currentAnim->frameHeight*2};
    button->onClickButton = onClickButton;
}

void Button_update(Button* button){

    Vector2 mousePosition = GetMousePosition();
    if(CheckCollisionPointRec(mousePosition,button->collider)){
        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            button->onClickButton(button);
        }
    }
}
void Button_draw(Button* button){
    Entity_draw(&button->entity);

}

void Button_unload(Button* button){
    Entity_unload(&button->entity);
}

void Build_Pet(Pet* pet){
    int petnum = GetRandomValue(0,PET_TYPES_NUM-1);
    switch (petnum)
    {
    case SHAREDIA:
        Pet_Init(pet,"../resources/sharedia.png",(Vector2){
            GetRandomValue(0,GetScreenWidth()-32.0),GetScreenHeight()-64.0});
        break;
    case ZERASUL:
        Pet_Init(pet,"../resources/zerasul.png",(Vector2){
             GetRandomValue(0,GetScreenWidth()-32.0),GetScreenHeight()-64.0});
    
    default:
        break;
    }
}
