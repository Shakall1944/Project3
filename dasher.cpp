/* This is Dasher game
 * Made by Lukas Kalan
 *
 */

#include "raylib.h"

// created own data type
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

// funtion for update of custom AnimData data type and animation
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
    windowDimensions[0] = 700; // width
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
    
    const int sizeOfNebulae{3};
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

    // variable for finish line
    float finishLine{ nebulae[sizeOfNebulae - 1].pos.x };
    
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
   
    // Texture initialization for background
    Texture2D background = LoadTexture("textures/far-buildings.png");
    float bgX{};

    // Texture initialization for midground
    Texture2D midground = LoadTexture("textures/back-buildings.png");
    float mgX{};

    // Texture initialization for foreground
    Texture2D foreground = LoadTexture("textures/foreground.png");
    float fgX{};

    // variable for collision checl
    bool collision{};

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        // delta time variable - time since last frame
        const float dT{GetFrameTime()};
        
        // Start drawing
        BeginDrawing();
        ClearBackground(WHITE);

        // variable for scrolling backround
        bgX -= 20 * dT;
        if (bgX <= -background.width*2)
        {
            bgX = 0.0;
        }
        // variable for scrolling midground
        mgX -= 40 * dT;
        if (mgX <= -midground.width*2)
        {
            mgX = 0.0;
        }
        // variable for scrolling foreground
        fgX -= 80 * dT;
        if (fgX <= -foreground.width*2)
        {
            fgX = 0.0;
        }
        
        // draw the background
        Vector2 bg1Pos{bgX, 0.0};
        DrawTextureEx(background, bg1Pos, 0.0, 3.0, WHITE);
        Vector2 bg2Pos{bgX + background.width*3, 0.0};
        DrawTextureEx(background, bg2Pos, 0.0, 3.0, WHITE);
        // draw the midground
        Vector2 mg1Pos{mgX, 0.0};
        DrawTextureEx(midground, mg1Pos, 0.0, 3.0, WHITE);
        Vector2 mg2Pos{mgX + midground.width*3, 0.0};
        DrawTextureEx(midground, mg2Pos, 0.0, 3.0, WHITE);
        // draw the foreground
        Vector2 fg1Pos{fgX, 0.0};
        DrawTextureEx(foreground, fg1Pos, 0.0, 2.5, WHITE);
        Vector2 fg2Pos{fgX + foreground.width*2.5, 0.0};
        DrawTextureEx(foreground, fg2Pos, 0.0, 2.5, WHITE);

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
        
        // update finish line
        finishLine += nebVel * dT;

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

        // collision detection loop
        for (AnimDate nebula : nebulae)
        {
            float pad{50};
            Rectangle nebRec{
                nebula.pos.x + pad,
                nebula.pos.y + pad,
                nebula.rec.width - 2*pad,
                nebula.rec.height - 2*pad,
            };
            Rectangle scarfyRec {
                scarfyData.pos.x,
                scarfyData.pos.y,
                scarfyData.rec.width,
                scarfyData.rec.height
            };
            if(CheckCollisionRecs(nebRec, scarfyRec))
            {
                collision = true;
            }
        }
        
        // check collision
        if (collision)
        {
            //lose the game
            DrawText("Game Over!", windowDimensions[0]/2, windowDimensions[1]/2, 50, RED);

        }
        else if (scarfyData.pos.x >= finishLine)
        {
            //win the game
            DrawText("You Win!", windowDimensions[0]/2, windowDimensions[1]/2, 50, RED);
        }
        
        else
        {
        // draw each nebula with "for" loop
        for (int i = 0; i < sizeOfNebulae; i++)
        {
            DrawTextureRec(nebula, nebulae[i].rec, nebulae[i].pos, WHITE);
        }
            // draw scarfy
            DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);
        }  
    
        
        //Stop drawing
        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    UnloadTexture(background);
    UnloadTexture(midground);
    UnloadTexture(foreground);
    CloseWindow();
    
}