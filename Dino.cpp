#include "Dino.hpp"

Dino::Dino()
{
    // default green dino
    this->setDinoColor(green);
    sprite = sf::Sprite(texture);
    sprite.setTextureRect( { 0,0,24,24 });
    color = green;
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
            texture.loadFromFile("Assets/dinos/green_dino.png");
            break;
        case red:
            texture.loadFromFile("Assets/dinos/red_dino.png");
            break;
        case blue:
            texture.loadFromFile("Assets/dinos/blue_dino.png");
            break;
        case yellow:
            texture.loadFromFile("Assets/dinos/yellow_dino.png");
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

void Dino::Draw(sf::RenderTarget& window)
{
    window.draw(this->sprite);
}



