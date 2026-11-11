#include <raylib.h>

int main()
{
    InitWindow(800, 600, "Bleh");
    Image img = LoadImage("dino/dino.png");
    if (!IsImageValid(img))
    {
        TraceLog(LOG_ERROR, "Could not Image");
    }
    else
    {
        SetWindowIcon(img);
    }
    OpenURL("https://youtu.be/AB3J8ufDYHQ?si=YyC7iBQQfyi4nT65");

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ShowCursor();
        ClearBackground(WHITE);
        EndDrawing();
    }
    if (IsImageValid(img))
    {
        UnloadImage(img);
    }

    CloseWindow();
}