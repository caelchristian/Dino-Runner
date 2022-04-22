#ifndef M4OEP_CCHRIST7_QWARDEN_DINO_H
#define M4OEP_CCHRIST7_QWARDEN_DINO_H
#include <iostream>
#include <vector>
#include <string>
#include "SFML/Graphics.hpp"
using namespace sf;

enum ColorDino
{
    green,
    yellow,
    red,
    blue
};

class Dino
{
private:
    float speed;
    ColorDino playerColor;
    Texture DinoTexture;

public:
    Dino();
};

#endif // M4OEP_CCHRIST7_QWARDEN_DINO_H