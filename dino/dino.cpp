#include "dino.hpp"

Dino::Dino()
{
    image = LoadTexture("dino/dino.png");
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