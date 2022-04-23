#ifndef M4OEP_CCHRIST7_QWARDEN_Animate_H
#define M4OEP_CCHRIST7_QWARDEN_Animate_H
#include <iostream>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
using namespace sf;

class Animate {
public:
    Animate(Texture* texture, Vector2u spriteDimensions, float totalAnimTime, float numOfFrames);
    virtual ~Animate() = 0;

    void update();
private:
    Vector2u currentFrame;
    Vector2u spriteDimensions;
    IntRect textureRect;
    float totalAnimTime;
    float timeBetweenFrames;
    float numOfFrames;
};

#endif