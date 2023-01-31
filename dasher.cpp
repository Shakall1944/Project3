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

// function for ground check
bool isOnGround(AnimDate data, int windowHeight)
{
    return data.pos.y >= windowHeight - data.rec.height;
}

// funtion for update of AnimData 
AnimDate updateAnimData(AnimDate data, float deltaTime, int maxFrame)
{
    // update running time
    data.runningTime += deltaTime;
    if (data.runningTime >= data.updateTime)
        {
            data.runningTime = 0.0;
            //update animation frame
            data.rec.x = data.frame * data.rec.width;
            data.frame++;
            if (data.frame > maxFrame)
            {
                data.frame = 0;
            }
            
        }
    return data;
}

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
    
    /* OLD CODE
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
    };*/
    
    const int sizeOfNebulae{10};
    // Array of nebula
    AnimDate nebulae[sizeOfNebulae]{};

    for (int i = 0; i < sizeOfNebulae; i++)
    {
        nebulae[i].rec.x = 0.0;
        nebulae[i].rec.y = 0.0;
        nebulae[i].rec.width = nebula.width/8;
        nebulae[i].rec.height = nebula.height/8;
        nebulae[i].pos.y = windowDimensions[1] - nebula.height/8;
        nebulae[i].frame = 0;
        nebulae[i].runningTime = 0.0;
        nebulae[i].updateTime = 1.0/12.0;
        nebulae[i].pos.x = windowDimensions[0] + i * 300;
    }


    
    /*nebulae[0].pos.x = windowDimensions[0];
    nebulae[1].pos.x = windowDimensions[0] + 300;
    nebulae[2].pos.x = windowDimensions[0] + 600;*/

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
        if (isOnGround(scarfyData, windowDimensions[1]))
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

        //update nebula position with for loops - each nebula
        for (int i = 0; i < sizeOfNebulae; i++)
        {
            nebulae[i].pos.x += (nebVel * dT);
        }
        
        //update scarfy postion + delta time
        scarfyData.pos.y += (velocity * dT);
        //check if scarfy is in the air, if yes do the animation 
        if (isInAir == false)
        {
            // OLD CODE - refactoring animation to function
            /*//update running time of scarfy
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
            }*/

            //new code with calling updateAnimdata function for animation
            scarfyData = updateAnimData(scarfyData, dT, 5);
        }

        // for loop for animation of nebulas
        for (int i = 0; i < sizeOfNebulae; i++)
        {
            //OLD CODE - refactoring animation to funtion
            /*//update running time of nebula
            nebulae[i].runningTime += dT;
            if (nebulae[i].runningTime >= nebulae[i].updateTime)
            {
            nebulae[i].runningTime = 0.0;
            //update animation frame of nebula
            nebulae[i].rec.x = nebulae[i].frame * nebulae[i].rec.width;
            nebulae[i].frame++;
            if ( nebulae[i].frame > 7)
                {
                 nebulae[i].frame = 0;
                }
            }*/

            //new code with calling updateAnimdata function for animation
            nebulae[i] = updateAnimData(nebulae[i], dT, sizeOfNebulae);
        }
        // draw each nebula with for loops
        for (int i = 0; i < sizeOfNebulae; i++)
        {
             DrawTextureRec(nebula, nebulae[i].rec, nebulae[i].pos, WHITE);
        }
        
        // draw scarfy
        DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);
        
        //Stop drawing
        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();
    
}