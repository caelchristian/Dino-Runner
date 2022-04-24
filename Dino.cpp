#include "Dino.hpp"

Dino::Dino()
{
    // default green dino
    this->setDinoColor(green);
    sprite = sf::Sprite(texture);
    sprite.setTextureRect( { 0,0,24,24 });
    color = green;
    hitBox.setSize(Vector2f(12,12));
}

Dino::Dino(ColorDino color)
{
    this->setDinoColor(color);
    this->color = color;
}

void Dino::setTexture(Texture dinoTexture)
{
    this->texture = dinoTexture;
}

void Dino::setSprite(Sprite sprite)
{
    this->sprite = sprite;
}

void Dino::setDinoColor(ColorDino color)
{
    switch (color)
    {
        case green:
            texture.loadFromFile("../assets/dinos/green_dino.png");
            break;
        case red:
            texture.loadFromFile("../assets/dinos/red_dino.png");
            break;
        case blue:
            texture.loadFromFile("../assets/dinos/blue_dino.png");
            break;
        case yellow:
            texture.loadFromFile("../assets/dinos/yellow_dino.png");
            break;
    }
}

const Texture& Dino::getTexture() const
{
    return this->texture;
}

const Sprite& Dino::getSprite() const
{
    return this->sprite;
}

const RectangleShape& Dino::getHitBox() const
{
    return this->hitBox;
}

void Dino::Draw(sf::RenderTarget& window)
{
    window.draw(this->sprite);
}

void Dino::nextFrame(IntRect& spriteFrame) const
{
    // if animation is at end of sprite sheet start over
    if (spriteFrame.left == 336)
    {
        spriteFrame.left = 0;
    }
    else
    {
        // else get next frame
        spriteFrame.left += 24;
    }
    // set the dino sprite texture rect to the new frame
    Sprite dinoSpriteRef = this->getSprite();
    dinoSpriteRef.setTextureRect(spriteFrame);
}

void Dino::update() {

}



