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

     // animation frame of scarfy
    int frame{};
    // amount of time before we update the animation frame of scarfy
    const float updateTime{1.0/12.0};
    float runningTime{};

    // nebula texture2D
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
    Rectangle nebRec{0.0, 0.0, nebula.width/8, nebula.height/8};
    Vector2 nebPos{windowsWidth, windowsHeight - nebRec.height};

    Rectangle neb2Rec{0.0, 0.0, nebula.width/8, nebula.height/8};
    Vector2 neb2Pos{windowsWidth + 300, windowsHeight - nebRec.height};


    //nebula x velocity (pixels/second)
    int nebVel{-200};
    // annimation frame of nebula
    int nebFrame{};
    // amount of time before we update the animation frame of nebula
    const float nebUpdateTime{1.0/12.0};
    float nebRunningTime{};

    int neb2Frame{};
    const float neb2UpdateTime{1.0/16.0};
    float neb2RunningTime{};

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
        //update 2nd nebula postion
        neb2Pos.x += (nebVel * dT);
        //update scarfy postion + delta time
        scarfyPos.y += (velocity * dT);
        //check if scarfy is in the air, if yes do the animation 
        if (isInAir == false)
        {
            //update running time of scarfy
            runningTime += dT;
            if (runningTime >= updateTime)
            {
                runningTime = 0.0;
                //update animation frame of scarfy
                scarfyRec.x = frame * scarfyRec.width;
                frame++;
                    if ( frame > 5)
                    {
                    frame = 0;
                    }
            }
        }

        //update running time of nebula
        nebRunningTime += dT;
        if (nebRunningTime >= nebUpdateTime)
        {
            nebRunningTime = 0.0;
            //update animation frame of nebula
            nebRec.x = nebFrame * nebRec.width;
            nebFrame++;
            if ( nebFrame > 7)
                {
                nebFrame = 0;
                }
        }

        //update running time of nebula
        neb2RunningTime += dT;
        if (neb2RunningTime >= neb2UpdateTime)
        {
            neb2RunningTime = 0.0;
            //update animation frame of nebula
            neb2Rec.x = neb2Frame * neb2Rec.width;
            neb2Frame++;
            if ( neb2Frame > 7)
                {
                neb2Frame = 0;
                }
        }
        
        // draw nebula
        DrawTextureRec(nebula, nebRec, nebPos, WHITE);
        // draw the 2nd nebula
        DrawTextureRec(nebula, neb2Rec, neb2Pos, RED);
        // draw scarfy
        DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);
        
        //Stop drawing
        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();
    
}