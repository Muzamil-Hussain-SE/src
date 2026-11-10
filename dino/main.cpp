#include <raylib.h>
#include "dino.hpp"


int main()
{
    InitWindow(800, 600, "Raylib Collisions");
    SetTargetFPS(60);
    Dino dino;

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);
        dino.draw();
        EndDrawing();
    }
}