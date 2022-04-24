#ifndef M4OEP_CCHRIST7_QWARDEN_DINO_H
#define M4OEP_CCHRIST7_QWARDEN_DINO_H
#include <iostream>
#include <vector>
#include <string>
#include "SFML/Graphics.hpp"
using namespace sf;

enum ColorDino{
    green,yellow,red,blue
};

class Dino {
private:
    ColorDino color;
    RectangleShape hitBox;
    Texture texture;
    Sprite sprite;

public:
    Dino();
    explicit Dino(ColorDino color);

    void setTexture(Texture dinoTexture);
    void setSprite(Sprite sprite);
    void setDinoColor(ColorDino color);
    const Texture& getTexture() const;
    const Sprite& getSprite() const;
    const RectangleShape& getHitBox() const;
    void nextFrame(IntRect& spriteFrame) const;
    void update();

    void Draw(sf::RenderTarget& window);

};

#endif //M4OEP_CCHRIST7_QWARDEN_DINO_H