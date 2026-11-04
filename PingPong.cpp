#include <bits/stdc++.h>
#include <raylib.h>
using namespace std;
int main()
{
    cout<<"Starting the game...\n";
    const int screen_height = 600;
    const int screen_width = 800;
    InitWindow(screen_width,screen_height,"Ping Pong"); //creating window
    SetTargetFPS(60);
    
    while(WindowShouldClose()==false)       //GameLoop
    {
        BeginDrawing();
        DrawCircle(screen_width/2,screen_height/2,10,WHITE);
        DrawRectangle(8,screen_height/2 - 60,25,120,WHITE);
        DrawRectangle(screen_width-33,screen_height/2 - 60,25,120,WHITE);

        EndDrawing();
    }


    CloseWindow();      //closing window
    return 0;
}