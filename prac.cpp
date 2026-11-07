#include <bits/stdc++.h>
#include <raylib.h>
using namespace std;

int main()
{
    int p1score = 0;
    int p2score = 0;
    int height = 600;
    int width = 800;
    InitWindow(800, 600, "Practice");
    SetTargetFPS(60);
    int x1 = 150;
    int y1 = 200;
    int x2 = 200;
    int y2 = 150;
    Rectangle leftRect = {0, 200, 20, 120};
    Rectangle rightRect = {(float)width - 20, (float)(height - 400), 20, 120};
    // int speedx = 5;
    // int speedy = 5;
    while (WindowShouldClose() == false)
    {
        BeginDrawing();

        ClearBackground(GREEN);
        DrawCircle(x1, y1, 15, YELLOW);
        DrawCircle(x2, y2, 15, GRAY);
        DrawRectangleRounded(rightRect, 0.8, 0, RED);
        DrawRectangleRounded(Rectangle{leftRect}, 0.8, 0, RED);
        if (y1 <= 0)
        {

            y1 = 10;
        }
        if (y1 >= height)
        {
            y1 = height - 10;
        }

        if (x1 >= width)
        {
            x1 = width - 10;
            ;
        }
        if (x1 <= 0)
        {
            x1 = 10;
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

            y2 = 10;
        }
        if (y2 >= height)
        {
            y2 = height - 10;
        }

        if (x2 >= width)
        {
            x2 = width - 10;
        }
        if (x2 <= 0)
        {
            x2 = 10;
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
        if (CheckCollisionCircleRec(Vector2{(float)x2, (float)y2}, 15, leftRect))
        {
            p2score++;
            cout << "Gray ball hit left rectangle!" << endl;
            x2 = width / 2;
        }
        if (CheckCollisionCircleRec(Vector2{(float)x1, (float)y1}, 15, rightRect))
        {
            p1score++;
            cout << "Yellow ball hit right rectangle!" << endl;
            x1 = width / 2;
        }
        DrawText(TextFormat("%i", p1score), width / 4 - 20, 20, 80, WHITE);
        DrawText(TextFormat("%i", p2score), 3 * width / 4 - 20, 20, 80, WHITE);

        EndDrawing();
    }
    CloseWindow();

    return 0;
}