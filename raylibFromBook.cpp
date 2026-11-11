#include<raylib.h>

int main()
{
    InitWindow(800,600,"Bleh");
    Image img = LoadImage("dino/dino.png");
    SetWindowIcon(img);

    CloseWindow();
}