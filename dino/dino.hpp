#pragma once
#include <raylib.h>

class Dino
{
    private:
    Texture2D image;
    Vector2 position; 
    public:
    Dino();
    ~Dino();
    void draw();
    void update();
};