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

    // accelaration due to gravity (pixel/frame)/frame + variable for jump
    //const int gravity{1};
    //accelaration due to gravity (pixel/s)/s
    const int gravity{1000};
    //const int jumpVel{-22};
    //jump velocity (pixels/second)
    const int jumpVel{-600};
    bool isInAir{false};

    // set up the variables for scarpy textures - raylib parameters
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    Rectangle scarfyRec;
    scarfyRec.width = scarfy.width/6;
    scarfyRec.height = scarfy.height;
    scarfyRec.x= 0;
    scarfyRec.y= 0;
    Vector2 scarfyPos;
    scarfyPos.x = windowsWidth/2 - scarfyRec.width/2;
    scarfyPos.y = windowsHeight - scarfyRec.height;

    // nebula texture2D
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
    Rectangle nebRec{0.0, 0.0, nebula.width/8, nebula.height/8};
    Vector2 nebPos{windowsWidth, windowsHeight - nebRec.height};
    //nebula x velocity (pixels/second)
    int nebVel{-600};


    // animation frame
    int frame{};
    // amount of time before we update the animation frame
    const float updateTime{1.0/12.0};
    float runningTime{};

    // rectangle dimenstions
    //const int width(50);
    //const int height(80);
    //int posY(windowsHeight - height);
    int velocity{0};
   

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        // Start drawing
        BeginDrawing();
        ClearBackground(WHITE);

        // delta time variable - time since last frame
        const float dT{GetFrameTime()};

        // ground check
        if (scarfyPos.y >= windowsHeight - scarfyRec.height)
        {
            // rectangle is on the ground
            velocity = 0;
            isInAir = false;
        }
        else 
        {
        // rectangle is in the air + delta time
            velocity += gravity * dT;
            isInAir = true;

        }
        // check for jumping
        if (IsKeyPressed(KEY_SPACE) && !isInAir)
        {
            velocity += jumpVel;
        }
        //update nebula position
        nebPos.x += (nebVel * dT);
        //update scarfy postion + delta time
        scarfyPos.y += (velocity * dT);
        //check if scarfy is in the air, if yes do the animation 
        if (isInAir == false)
        {
            //update running time
            runningTime += dT;
            if (runningTime >= updateTime)
            {
            runningTime = 0.0;
            //update animation frame
            scarfyRec.x = frame * scarfyRec.width;
            frame++;
                if ( frame > 5)
                {
                frame = 0;
                }
            }
        }
        
        // draw nebula
        DrawTextureRec(nebula, nebRec, nebPos, WHITE);
        // draw scarfy
        DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);
        
        //Stop drawing
        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();
    
}