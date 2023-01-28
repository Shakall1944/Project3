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

    // accelaration due to gravity (pixel/frame)/frame
    const int gravity{1};
    const int jumpVel{-22};
    bool isInAir(false);

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


        // ground check
        if (posY >= windowsHeight - height)
        {
            // rectangle is on the ground
            velocity = 0;
            isInAir = false;
        }
        else 
        {
        // rectangle is in the air
            velocity += gravity;
            isInAir = true;

        }
        // check for jumping
        if (IsKeyPressed(KEY_SPACE) && !isInAir)
        {
            velocity += jumpVel;
        }
        //update Y postion
        posY += velocity;
    
        DrawRectangle(windowsWidth/2, posY, width, height, BLUE);
        
        //Stop drawing
        EndDrawing();
    }
    CloseWindow();
    
}