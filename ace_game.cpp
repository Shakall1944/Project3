/*
 * The AXE Game
 * Made by Lukas Kalan
 * 
 */

#include "raylib.h"
int main()
{
    // Declaration of variables - window dimensions
    int width{800};
    int height{450};
    //Running raylib
    InitWindow(width, height, "Lukas's Window");

    //circle coordinates
    int circle_x{200};
    int circle_y{200};

    //Axe coordinates
    int axe_x{400};
    int axe_y{0};

    int direction{10};
    
    SetTargetFPS(60);
    while ( WindowShouldClose() == false )
    {
        BeginDrawing();
        ClearBackground(WHITE);

        //Game login begins!
        DrawCircle(circle_x, circle_y, 25, BLUE);
        DrawRectangle(axe_x, axe_y, 50, 50, RED);

        // move the axe
        axe_y += direction;
        if (axe_y > 450 || axe_y < 0 )
        {
            direction = -direction;
        }
        

        if (IsKeyDown(KEY_D) && circle_x < 350 )
        {
            circle_x += 10;
        }
        
        if (IsKeyDown(KEY_A) && circle_x > 0 )
        {
            circle_x -= 10;
        }
        
        /*if (IsKeyDown(KEY_W))
        {
            circle_y = circle_y - 10;
        }

        if (IsKeyDown(KEY_S))
        {
            circle_y = circle_y + 10;
        }*/
        
        //Game logic ends!
        EndDrawing();
    }
    
}