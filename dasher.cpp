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
    //1st Array - Set dimension of window
    int  windowDimensions[2];
    windowDimensions[0] = 800; // width
    windowDimensions[1] = 450; // height
    /* OLD CODe - Set dimension of window 
    const int windowsWidth{800};
    const int windowsHeight{450};*/
    //
    InitWindow(windowDimensions[0], windowDimensions[1], "Lukas's game!");

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
    scarfyData.pos.x = windowDimensions[0]/2 - scarfyData.rec.width/2;
    scarfyData.pos.y = windowDimensions[1] - scarfyData.rec.height;
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
        {windowDimensions[0], windowDimensions[1] - nebula.height/8}, //vector2 pos
        0, // int frame
        1.0/12, //float updatetime
        0 // float running time
    };

    AnimDate neb2Data{
        {0.0, 0.0, nebula.width/8, nebula.height/8},
        {windowDimensions[0] + 300, windowDimensions[1] - nebula.height/8},
        0,
        1.0/12,
        0
    };
    // Array of nebula
    AnimDate nebulae[2] { nebData, neb2Data, };

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
        if (scarfyData.pos.y >= windowDimensions[1] - scarfyData.rec.height)
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
        nebulae[0].pos.x += (nebVel * dT);
        //update 2nd nebula postion
        nebulae[1].pos.x += (nebVel * dT);
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
        nebula[0].runningTime += dT;
        if (nebulae[0].runningTime >= nebulae[0].updateTime)
        {
            nebulae[0].frame = 0.0;
            //update animation frame of nebula
            nebulae[0].rec.x = nebulae[0].frame * nebulae[0].rec.width;
            nebulae[0].frame++;
            if ( nebulae[0].frame > 7)
                {
                nebulae[0].frame = 0;
                }
        }

        //update running time of 2nd nebula
        nebulae[1].runningTime += dT;
        if (neb2Dnebulae[1]ata.runningTime >= nebulae[1].updateTime)
        {
            nebulae[1].runningTime = 0.0;
            //update animation frame of nebula
            nebulae[1].rec.x = nebulae[1].frame * nebulae[1].rec.width;
            nebulae[1].frame++;
            if ( nebulae[1].frame > 7)
                {
                nebulae[1].frame = 0;
                }
        }
        
        // draw nebula
        DrawTextureRec(nebula, nebulae[0].rec, nebulae[0].pos, WHITE);
        // draw the 2nd nebula
        DrawTextureRec(nebula, nebulae[1].rec, nebulae[1].pos, RED);
        // draw scarfy
        DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);
        
        //Stop drawing
        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();
    
}