/* This is Dasher game
 * Made by Lukas Kalan
 *
 */

#include "raylib.h"

struct AnimDate
{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;
};


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

    // AnimData for scarfy
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    AnimDate scarfyData;
    scarfyData.rec.width = scarfy.width/6;
    scarfyData.rec.height = scarfy.height;
    scarfyData.rec.x = 0;
    scarfyData.rec.y = 0;
    scarfyData.pos.x = windowsWidth/2 - scarfyData.rec.width/2;
    scarfyData.pos.y = windowsHeight - scarfyData.rec.height;
    scarfyData.frame = 0;
    scarfyData.updateTime = 1.0/12.0;
    scarfyData.runningTime = 0.0;
    
    /* OLD CODE from previuos lessons
    // set up the variables for scarpy textures - raylib parameters
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
    */

    // nebula texture2D
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
    
    //AnimData for nebula
    AnimDate nebData{ 
        {0.0, 0.0, nebula.width/8, nebula.height/8}, //rectangle rec
        {windowsWidth, windowsHeight - nebula.height/8}, //vector2 pos
        0, // int frame
        1.0/12, //float updatetime
        0 // float running time
    };

    AnimDate neb2Data{
        {0.0, 0.0, nebula.width/8, nebula.height/8},
        {windowsWidth + 300, windowsHeight - nebula.height/8},
        0,
        1.0/12,
        0
    };

    // OLD CODE from previuos lessons
    
    /* annimation frame of nebula
    int nebFrame{};
    // amount of time before we update the animation frame of nebula
    const float nebUpdateTime{1.0/12.0};
    float nebRunningTime{};

    int neb2Frame{};
    const float neb2UpdateTime{1.0/16.0};
    float neb2RunningTime{};
    
    
    Rectangle nebRec{0.0, 0.0, nebula.width/8, nebula.height/8};
    Vector2 nebPos{windowsWidth, windowsHeight - nebRec.height};

    Rectangle neb2Rec{0.0, 0.0, nebula.width/8, nebula.height/8};
    Vector2 neb2Pos{windowsWidth + 300, windowsHeight - nebRec.height};
    

    annimation frame of nebula
    int nebFrame{};
    // amount of time before we update the animation frame of nebula
    const float nebUpdateTime{1.0/12.0};
    float nebRunningTime{};

    int neb2Frame{};
    const float neb2UpdateTime{1.0/16.0};
    float neb2RunningTime{}; */
    
    
    //nebula x velocity (pixels/second)
    int nebVel{-200};

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
        if (scarfyData.pos.y >= windowsHeight - scarfyData.rec.height)
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
        nebData.pos.x += (nebVel * dT);
        //update 2nd nebula postion
        neb2Data.pos.x += (nebVel * dT);
        //update scarfy postion + delta time
        scarfyData.pos.y += (velocity * dT);
        //check if scarfy is in the air, if yes do the animation 
        if (isInAir == false)
        {
            //update running time of scarfy
            scarfyData.runningTime += dT;
            if (scarfyData.runningTime >= scarfyData.updateTime)
            {
                scarfyData.runningTime = 0.0;
                //update animation frame of scarfy
                scarfyData.rec.x = scarfyData.frame * scarfyData.rec.width;
                scarfyData.frame++;
                    if ( scarfyData.frame > 5)
                    {
                         scarfyData.frame = 0;
                    }
            }
        }

        //update running time of nebula
        nebData.runningTime += dT;
        if (nebData.runningTime >= nebData.updateTime)
        {
            nebData.frame = 0.0;
            //update animation frame of nebula
            nebData.rec.x = nebData.frame * neb2Data.rec.width;
            nebData.frame++;
            if ( nebData.frame > 7)
                {
                nebData.frame = 0;
                }
        }

        //update running time of 2nd nebula
        neb2Data.runningTime += dT;
        if (neb2Data.runningTime >= neb2Data.updateTime)
        {
            neb2Data.runningTime = 0.0;
            //update animation frame of nebula
            neb2Data.rec.x = neb2Data.frame * neb2Data.rec.width;
            neb2Data.frame++;
            if ( neb2Data.frame > 7)
                {
                neb2Data.frame = 0;
                }
        }
        
        // draw nebula
        DrawTextureRec(nebula, nebData.rec, nebData.pos, WHITE);
        // draw the 2nd nebula
        DrawTextureRec(nebula, neb2Data.rec, neb2Data.pos, RED);
        // draw scarfy
        DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);
        
        //Stop drawing
        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();
    
}