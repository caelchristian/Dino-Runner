//
// Created by Cael Christian on 4/19/22.
//

#include "DinoGame.hpp"

void DinoGame::initVars()
{
    runSpeed = 100;
    gameState = runState;
    groundHeight = 300;
    jumpSpeed = 3.0f;
}

void DinoGame::initClock()
{
    return;
}

void DinoGame::initSprites()
{
    bgTexture.loadFromFile("../assets/bg1.png");
    this->bgSprite = new Sprite(bgTexture);
}

void DinoGame::initWindow()
{
    // initialize window
    this->videoMode = sf::VideoMode(WINDOWWIDTH, WINDOWHEIGHT);
    this->window = new sf::RenderWindow(this->videoMode, "Dino Game", sf::Style::Close | sf::Style::Titlebar);
    this->window->setFramerateLimit(60);
}

DinoGame::DinoGame()
{
    initVars();
    initWindow();

    // TODO: initialize sprites/shapes
    // initSprites();

    // TODO: initialize clock
    // initClock();

    // TODO: Initialize Text
}

// TODO: Jump Function after Dino class is completed
// const void DinoGame::jump(float yVelocity, float jumpHight) {
//     if (canJumpVar) {
//         canJumpVar = false;
//         this->dinoSprite
//     }
// }

const bool DinoGame::isWindowOpen()
{
    return this->window->isOpen();
}

const sf::RenderTarget &DinoGame::getWindow()
{
    return *this->window;
}

// const void DinoGame::canJump() const {
// if (this->dino
// }

// void DinoGame::repositionView(View &view) {
//     float aspectRatio = float(window->getSize().x) / float(window->getSize().y);

//     view.setSize()
// }

// void DinoGame::drawBackground()
//{
//     // TODO: Reposition background to fit window
//     this->window->draw(*bgSprite);
// }

void DinoGame::pollEvents()
{
    while (this->window->pollEvent(this->event))
    {
        switch (this->event.type)
        {
        case sf::Event::Closed:
            this->window->close();
            break;
        case sf::Event::KeyPressed:
            if (this->event.key.code == sf::Keyboard::Escape)
                this->window->close();
            break;
        default:
            break;
        }
    }
}

void DinoGame::render()
{
    for (auto &o : obstacles)
    {
        this->window->draw(o);
    }
    // this->window->draw(player);
}

void DinoGame::mainLoop()
{

    while (this->window->isOpen() && (gameState == startState))
    {
        // poll to quit game
        while (this->window->pollEvent(this->event))
        {
            // if user closes window, end
            switch (event.type)
            {
            case sf::Event::Closed:
                window->close();
                break;
                // if user presses escape, end
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Escape)
                    window->close();
                break;
            default:
                break;
            }
        }

        if (this->gameState == startState)
        {
            // this->updateTerrain();
            // this->spawnObstacles();

            // update dino position if jump
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
                velocity.x = jumpSpeed;

            // store reference to Dino IntRect hitbox
            RectangleShape hitBox = this->dino.getHitBox();
            hitBox.move(velocity.x, velocity.y);

            // if the hitBox is below peak height, increase upwards velocity
            if (hitBox.getPosition().y + hitBox.getSize().y < groundHeight)
                velocity.y += GRAVITY;
            // else set position to ground height - hitBox height
            else
            {
                velocity.y = 0;
                hitBox.setPosition(hitBox.getPosition().x, groundHeight - hitBox.getSize().y);
            }

            // this->updateCollision();
        }

        // Run Animation Dino Clock
        if (clock.getElapsedTime().asSeconds() > .1f)
        {
            dino.nextFrame(dinoIntRect);
            clock.restart();
        }

        // clear frame
        window->clear();

        /* Draw here */
        window->draw(dino.getSprite());
        this->render();

        // display frame
        window->display();
    }
}

// actually don't think ill need this if since window is global var
// const sf::RenderTarget& Game::get_window() const {
//     return this->window;
// }
