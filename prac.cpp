#include <bits/stdc++.h>
#include <raylib.h>
using namespace std;

int main()
{

    InitWindow(800, 600, "Practice");
    SetTargetFPS(60);
    int x = 150;
    int y=200;
    while (WindowShouldClose() == false)
    {
        BeginDrawing();


        ClearBackground(GREEN);
        DrawCircle(x, y, 15, YELLOW);
        DrawRectangleRounded(Rectangle{200,200,120,20},0.8,0,RED);
        if(IsKeyDown(KEY_W))
        {
            y-=10;
        }
        if(IsKeyDown(KEY_S))
        {
            y+=10;
        }if(IsKeyDown(KEY_A))
        {
            x-=10;
        }if(IsKeyDown(KEY_D))
        {
            x+=10;
        }

        EndDrawing();
    }
    CloseWindow();

    return 0;
}