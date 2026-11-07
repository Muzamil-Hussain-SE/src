#include <bits/stdc++.h>
#include <raylib.h>
using namespace std;

int main()
{
    int height = 600;
    int width = 800;
    InitWindow(800, 600, "Practice");
    SetTargetFPS(60);
    int x = 150;
    int y = 200;
    // int speedx = 5;
    // int speedy = 5;
    while (WindowShouldClose() == false)
    {
        BeginDrawing();

        ClearBackground(GREEN);
        DrawCircle(x, y, 15, YELLOW);
        DrawRectangleRounded(Rectangle{200, 200, 120, 20}, 0.8, 0, RED);
        if (y <= 0)
        {

            y = height;
        }
        if (y >= height)
        {
            y = 0;
        }

        if (x >= width)
        {
            x = 0;
        }
        if (x <= 0)
        {
            x = width;
        }

        if (IsKeyDown(KEY_W))
        {
            y -= 10;
        }
        if (IsKeyDown(KEY_S))
        {
            y += 10;
        }
        if (IsKeyDown(KEY_A))
        {
            x -= 10;
        }
        if (IsKeyDown(KEY_D))
        {
            x += 10;
        }

        EndDrawing();
    }
    CloseWindow();

    return 0;
}