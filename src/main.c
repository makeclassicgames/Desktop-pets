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

#include <raylib.h>
#include "entity.h"
#include "timer.h"

#define MAX_ENTITIES 10

#define WINDOW_WIDTH 450
#define WINDOW_HEIGHT 450

#define RECT_WIDTH 100
#define RECT_HEIGHT 100

void init(void);
void update(void);
void draw(void);

void onTimer(void);

Entity entity[MAX_ENTITIES];
int entityCount = 0;
Timer timer;

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
    while (!WindowShouldClose()) // Detect window close button or ESC key
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
    for(int i=0;i<entityCount;i++){
            Entity_unload(&entity[i]);
    }
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
    entityCount = 2;
    
    Entity_init(&entity[0],"../resources/zerasul.png",(Vector2){100,GetScreenHeight()-64},(Vector2){100.0,0});
    Sprite_setAnimation(&entity[0].sprite,1);
    Entity_init(&entity[1],"../resources/sharedia.png",(Vector2){100+50,GetScreenHeight()-64},(Vector2){0.0,0});
    Sprite_setAnimation(&entity[1].sprite,2);
    
    Timer_init(&timer, 4, true, true,onTimer);

    TraceLog(LOG_INFO,"Init finalizado");

}

void update(void)
{
    for(int i=0;i<entityCount;i++){
        Entity_update(&entity[i]);
    }
    Timer_update(&timer);
}

void draw(void)
{

    for (int i = 0; i < entityCount; i++)
    {
        Entity_draw(&entity[i]);
    }
    
}

void onTimer(void){
    entity[0].velocity.x= -entity[0].velocity.x;
    if(entity[0].velocity.x>0){
        Sprite_setAnimation(&entity[0].sprite,1);
    }else{
        Sprite_setAnimation(&entity[0].sprite,3);
    }
}