#include "dino.hpp"

Dino::Dino()
{
    image = LoadTexture("dino.png");
    position.x = 100;
    position.y = 100;
};
Dino::~Dino()
{
    UnloadTexture(image);
}
void Dino::draw()
{
    DrawTextureV(image,position,WHITE);
}