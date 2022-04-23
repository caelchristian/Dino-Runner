#include <iostream>
#include <vector>
#include <string>
#include "SFML/Graphics.hpp"
#include "Animate.hpp"

Animate::Animate(Texture* texture, Vector2u spriteDimensions, float totalAnimTime, float numOfFrames) {
    this->totalAnimTime = totalAnimTime;
    this->numOfFrames = numOfFrames;
    this->spriteDimensions = spriteDimensions;
    timeBetweenFrames = (totalAnimTime / numOfFrames);

    // initialize animation time to 0
    totalAnimTime = 0.f;
    currentFrame.x = 0.f;
}

void Animate::update() {
    totalAnimTime += timeBetweenFrames;
    if (totalAnimTime >= timeBetweenFrames) {
        totalAnimTime -= timeBetweenFrames;
    }
}