#include <raylib.h>
#include "ball.h"
int main()
{
    int ballX = 300;
    int ballY = 300;

    InitWindow(600, 600, "New Game");
    SetTargetFPS(60);

    // Game loop
    while (WindowShouldClose() == false)
    {
        ballX += 3;
        BeginDrawing();
        // DrawCircle(280,160,13,WHITE);
        // DrawRectangle(270,170,20,120,WHITE);
        // DrawCircle(260,300,20,WHITE);
        ClearBackground(BLACK);
        DrawCircle(ballX, ballY, 20, WHITE);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
// Simple ball game

// Color darkgreen = Color{20,160,133,255};

// const int screenWidth = 800;
// const int screenHeight = 600;

// Ball ball = Ball();

// InitWindow(screenWidth,screenHeight,"My First RAYLIB game! ");
// SetTargetFPS(60);

// while(!WindowShouldClose())
// {
//     BeginDrawing();
//     ClearBackground(darkgreen);
//     ball.Update();
//     ball.Draw();
//     EndDrawing();
// }
// CloseWindow();