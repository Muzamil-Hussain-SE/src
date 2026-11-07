#include <bits/stdc++.h>
#include <raylib.h>
using namespace std;

int main()
{
    int height = 600;
    int width = 800;
    InitWindow(800, 600, "Practice");
    SetTargetFPS(60);
    int x1 = 150;
    int y1 = 200;
    int x2 = 200;
    int y2 = 150;
    // int speedx = 5;
    // int speedy = 5;
    while (WindowShouldClose() == false)
    {
        BeginDrawing();

        ClearBackground(GREEN);
        DrawCircle(x1, y1, 15, YELLOW);
        DrawCircle(x2, y2, 15, GRAY);
        DrawRectangleRounded(Rectangle{0, 200, 20, 120}, 0.8, 0, RED);
        DrawRectangleRounded(Rectangle{(float)width - 20, (float)(height - 400), 20, 120}, 0.8, 0, RED);
        if (y1 <= 0)
        {

            y1 = height;
        }
        if (y1 >= height)
        {
            y1 = 0;
        }

        if (x1 >= width)
        {
            x1 = 0;
        }
        if (x1 <= 0)
        {
            x1 = width;
        }

        if (IsKeyDown(KEY_W))
        {
            y1 -= 10;
        }
        if (IsKeyDown(KEY_S))
        {
            y1 += 10;
        }
        if (IsKeyDown(KEY_A))
        {
            x1 -= 10;
        }
        if (IsKeyDown(KEY_D))
        {
            x1 += 10;
        }
        if (y2 <= 0)
        {

            y2 = height;
        }
        if (y2 >= height)
        {
            y2 = 0;
        }

        if (x2 >= width)
        {
            x2 = 0;
        }
        if (x2 <= 0)
        {
            x2 = width;
        }

        if (IsKeyDown(KEY_UP))
        {
            y2 -= 10;
        }
        if (IsKeyDown(KEY_DOWN))
        {
            y2 += 10;
        }
        if (IsKeyDown(KEY_LEFT))
        {
            x2 -= 10;
        }
        if (IsKeyDown(KEY_RIGHT))
        {
            x2 += 10;
        }

        EndDrawing();
    }
    CloseWindow();

    return 0;
}