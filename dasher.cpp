#include "raylib.h";
int main()
{
    //Set dimension of window
    int width{800};
    int height{450};
    InitWindow(width, height, "Lukas's game'");

    SetTargetFPS(60);
    while (true)
    {
        BeginDrawing();
        ClearBackground(WHITE);
        EndDrawing();
    }
    


}