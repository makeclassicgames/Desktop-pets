/*******************************************************************************************
 *
 *   raylib [shape] example - Translation, rotation and scaling
 *
 *   Example complexity rating: [★☆☆☆] 1/4
 *
 *   Example originally created with raylib 5.5, last time updated with raylib 5.6
 *
 *   Example contributed by zerasul (@zerasul) and reviewed by Ramon Santamaria (@raysan5)
 *
 *   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
 *   BSD-like license that allows static linking with closed source software
 *
 *   Copyright (c) 2025 zerasul (@zerasul) - All rights reserved.
 *
 ********************************************************************************************/
#include<stdio.h>
#include <stdlib.h>
#include <raylib.h>
#include "entity.h"
#include "timer.h"

#define MAX_ENTITIES 10

#define WINDOW_WIDTH 450
#define WINDOW_HEIGHT 250

#define RECT_WIDTH 100
#define RECT_HEIGHT 100

enum scenes{
    PETS,
    SETTINGS
};

struct _PetScene{
    Pet pets[MAX_ENTITIES];
    int petsCount;
    Button closeButton;
    Button menuButton;
    Button AddButton;
} petScene;

struct _SettingsScene{
  Button closeButton;
  Button backButton;
} settingsScene;

int currentScene;

void init(void);
void update(void);
void draw(void);

void init_pet_scene(void);
void update_pet_scene(void);
void draw_pet_scene(void);
void unload_pet_scene(void);

void init_settings_scene(void);
void update_settings_scene(void);
void draw_settings_scene(void);
void unload_settings_scene(void);


void unload_scenes(void);


void onTimer(void);
void onClickButton(void* buttonRef);
void onMenuClickButton(void* buttonRef);
void onBackClickButton(void* buttonRef);
void onAddClickButton(void* buttonRef);



bool windowRunning = true;

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------

    init();

    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose() && windowRunning) // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        update();

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(ColorAlpha(BLACK, 0.0f));
        draw();
        EndDrawing();
        //----------------------------------------------------------------------------------
    }
    for(int i=0;i<petScene.petsCount;i++){
            Entity_unload(&petScene.pets[i].entity);
    }
    Entity_unload(&petScene.closeButton.entity);
    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

void init(void)
{

    SetConfigFlags(FLAG_WINDOW_UNDECORATED | FLAG_WINDOW_TRANSPARENT | FLAG_WINDOW_TOPMOST);
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Virtual Pet");
    SetWindowPosition(GetMonitorWidth(0) - GetScreenWidth(), GetMonitorHeight(0) - GetScreenHeight());
    SetTargetFPS(60);

    currentScene = PETS;
    init_pet_scene();
    init_settings_scene();
    TraceLog(LOG_INFO,"Init finalizado");

}

void update(void)
{

    switch (currentScene)
    {
    case PETS:
        update_pet_scene();
        break;
    case SETTINGS:
        update_settings_scene();
        break;
    default:
        break;
    }
}

void draw(void)
{
    switch (currentScene)
    {
    case PETS:
        draw_pet_scene();
        break;
    case SETTINGS:
        draw_settings_scene();
    
    default:
        break;
    }
    
}

void onTimer(void){
    petScene.pets[0].entity.velocity.x= -petScene.pets[0].entity.velocity.x;
    if(petScene.pets[0].entity.velocity.x>0){
        Sprite_setAnimation(&petScene.pets[0].entity.sprite,1);
    }else{
        Sprite_setAnimation(&petScene.pets[0].entity.sprite,3);
    }
}

void onClickButton(void* buttonRef){
    Button* button = (Button*)buttonRef;
    if(CheckCollisionPointRec(GetMousePosition(),button->collider)){
        TraceLog(LOG_INFO,"Button Clicked");
        windowRunning = false;
    }
}

void unloadScenes(void){
    unload_pet_scene();
    unload_settings_scene();
}




//Pet Scene

void init_pet_scene(void){
    petScene.petsCount = 2;
    
    for(size_t i = 0; i<petScene.petsCount;i++){
        Build_Pet(&petScene.pets[i]);
    }
    Button_init(&petScene.closeButton,"../resources/closeButton.png",(Vector2){GetScreenWidth()-32,0},onClickButton);
    Button_init(&petScene.menuButton,"../resources/menuButton.png",(Vector2){GetScreenWidth()-64.0,0},onMenuClickButton);
    Button_init(&petScene.AddButton,"../resources/addButton.png",(Vector2){GetScreenWidth()-96.0,0},onAddClickButton);
}

void update_pet_scene(void){
    for(int i=0;i<petScene.petsCount;i++){
        Pet_update(&petScene.pets[i]);
    }
    Button_update(&petScene.closeButton);
    Button_update(&petScene.menuButton);
    Button_update(&petScene.AddButton);
}

void draw_pet_scene(void){

    for (int i = 0; i < petScene.petsCount; i++)
    {
        Pet_draw(&petScene.pets[i]);
    }
    Button_draw(&petScene.closeButton);
    Button_draw(&petScene.menuButton);
    Button_draw(&petScene.AddButton);
}


void unload_pet_scene(void){
    for(size_t i =0;i<petScene.petsCount;i++){
        Entity_unload(&petScene.pets[i].entity);
    }
    Button_unload(&petScene.closeButton);
    Button_unload(&petScene.menuButton);
    Button_unload(&petScene.AddButton);

}


//Settings Scene

void init_settings_scene(void){
    Button_init(&settingsScene.closeButton,"../resources/closeButton.png",(Vector2){GetScreenWidth()-32,0},onClickButton);
    Button_init(&settingsScene.backButton,"../resources/backButton.png",(Vector2){GetScreenWidth()-64.0,0},onBackClickButton);
}

void update_settings_scene(void){
    Button_update(&settingsScene.closeButton);
    Button_update(&settingsScene.backButton);
}
void draw_settings_scene(void){
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), BLACK);
    Button_draw(&settingsScene.closeButton);
    Button_draw(&settingsScene.backButton);
    
}

void unload_settings_scene(void){
    Button_unload(&settingsScene.closeButton);
    Button_unload(&settingsScene.backButton);
}


void onMenuClickButton(void* buttonRef){
    currentScene = SETTINGS;
}

void onBackClickButton(void* buttonRef){
     currentScene = PETS;
}

void onAddClickButton(void* buttonRef){
    if(petScene.petsCount<MAX_ENTITIES){
        Build_Pet(&petScene.pets[petScene.petsCount]);
        petScene.petsCount++;
    }
}
