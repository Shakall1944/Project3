/*
 * The AXE Game
 * Made by Lukas Kalan
 * 
 */

#include "raylib.h"
int main()
{
    // Variables of program
    //false
    bool equal{ 4 == 9 };
    //true
    bool notEqual{ 4 != 9 };
    //true
    bool less{ 4 < 9 };
    //false
    bool greater{ 4 > 9 };
    //true
    bool lessEqual{ 4 <= 9 };
    //false
    bool greaterEqual{ 4 >= 9 };
    // Declaration of variables
    int width;
    width = 350;
    //Running raylib
    InitWindow(width, 300, "Lukas's Window");
}