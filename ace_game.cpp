/*
 * The AXE Game
 * Made by Lukas Kalan
 * 
 */

#include "raylib.h"
int main()
{
    // Declaration of variables
    int width;
    width = 350;
    //Running raylib
    InitWindow(width, 300, "Lukas's Window");
    
    while (true)
    {
        BeginDrawing();
        ClearBackground(RED);
        EndDrawing();
    }
    
}