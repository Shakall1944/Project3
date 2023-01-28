/* This is Dasher game
 * Made by Lukas Kalan
 *
 */

#include "raylib.h"
int main()
{
    //Set dimension of window
    const int windowsWidth{800};
    const int windowsHeight{450};
    //
    InitWindow(windowsWidth, windowsHeight, "Lukas's game!");

    // rectangle dimenstions
    const int width(50);
    const int height(80);

    int posY(windowsHeight - height);
    int velocity{0};

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        // Start drawing
        BeginDrawing();
        ClearBackground(WHITE);

        if (IsKeyPressed(KEY_SPACE))
        {
            velocity -= 10;
        }
        
        posY += velocity;

        DrawRectangle(windowsWidth/2, posY, width, height, BLUE);
        
        //Stop drawing
        EndDrawing();
    }
    CloseWindow();
    
}