#include<raylib.h>
#include "ball.h"
int main()
{
    Color darkgreen = Color{20,160,133,255};
    
    const int screenWidth = 800;
    const int screenHeight = 600;

    Ball ball = Ball();

    InitWindow(screenWidth,screenHeight,"My First RAYLIB game! ");
    SetTargetFPS(60);

    while(!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(darkgreen);
        ball.Update();
        ball.Draw();
        EndDrawing();
    }
    CloseWindow();

    return 0;
}