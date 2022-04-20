#ifndef M4OEP_CCHRIST7_QWARDEN_Animate_H
#define M4OEP_CCHRIST7_QWARDEN_Animate_H
#include <iostream>
#include <vector>
#include <string>
#include "SFML/Graphics.hpp"
using namespace sf;

class Animate {
    public:
        Animate(Texture *texture, float totalAnimTime, Vector2u spriteSize);
        ~Animate();
        void update(int row,)

    private:
        Vector2u spriteCount;
        Vector2u currentFrame;
        IntRect textureRect;

        float totalAnimTime;
}


#endif