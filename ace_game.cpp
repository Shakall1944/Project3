/*
 * The AXE Game
 * Made by Lukas Kalan
 * 
 */

#include "raylib.h"
int main()
{
    // Declaration of variables - window dimensions
    int width{350};
    int height{200};
    //Running raylib
    InitWindow(width, height, "Lukas's Window");

    //circle coordinates
    int circle_x{175};
    int circle_y{100};
    
    SetTargetFPS(60);
    while ( WindowShouldClose() == false )
    {
        BeginDrawing();
        ClearBackground(WHITE);

        //Game login begins!
        DrawCircle(circle_x, circle_y, 25, BLUE);

        if (IsKeyDown(KEY_D) && circle_x < 350 )
        {
            circle_x = circle_x + 10;
        }
        
        if (IsKeyDown(KEY_A) && circle_x > 0 )
        {
            circle_x = circle_x - 10;
        }
        
        if (IsKeyDown(KEY_W))
        {
            circle_y = circle_y - 10;
        }

        if (IsKeyDown(KEY_S))
        {
            circle_y = circle_y + 10;
        }
        
        //Game logic ends!
        EndDrawing();
    }
    
}