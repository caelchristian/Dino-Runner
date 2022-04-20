//
// Created by Cael Christian on 4/19/22.
//

#include "DinoGame.h"


DinoGame::DinoGame() {
    void init();
}

void DinoGame::initVars() {
    health = 3;
    runSpeed = 100;
    gameState = startState;
}

void DinoGame::initSprites() {
    // Default Green Dino
        if(!dinoTexture.loadFromFile("Assets/dinos/green_dino.png")) {
        std::cout << "Green dino image not loaded" << std::endl;
    } else {
        // first frame of animation
        this->dinoSprite = new Sprite(dinoTexture, dinoAnim);
    }
}

// TODO: Jump Function after Dino class is completed 
// const void DinoGame::jump(float yVelocity, float jumpHight) {
//     if (canJumpVar) {
//         canJumpVar = false;
//         this->dinoSprite
//     }
// }

void DinoGame::init() {
    // initialize window
    this->videoMode = sf::VideoMode(WINDOWWIDTH, WINDOWHEIGHT);
	this->window = new sf::RenderWindow(this->videoMode, "Dino Game", sf::Style::Close | sf::Style::Titlebar);
	this->window->setFramerateLimit(60);
    
    // Grass
    if(!bgTexture.loadFromFile("Assets/bg1.png")) {
        std::cout << "Background image not loaded" << std::endl;
    } else {
        this->bgSprite = new Sprite(bgTexture);
    }

    // TODO: initialize variables
    initVars();

    // TODO: initialize sprites/shapes
    initSprites();

    // TODO: initialize clock
    initClock();

    // TODO: Initialize Text 
}

const bool DinoGame::hasGameEnded() {
    this->window->isOpen();
}

// void DinoGame::repositionView(View &view) {
//     float aspectRatio = float(window->getSize().x) / float(window->getSize().y);

//     view.setSize()
// }

void DinoGame::drawBackground() {
    // TODO: Reposition background to fit window
    this->window->draw(*bgSprite);
}


void DinoGame::render() {
    for (auto& o : obstacles) {
        this->window->draw(o);
    }
    // this->window->draw(player);
}

void DinoGame::run() {

    

    Clock clock;



    while (this->isWindowOpen() && !(this->hasGameEnded())) {
    // poll to quit game
        while (this->window->pollEvent(this->event))
        {
            // if user closes window, end
            switch (event.type) {
            case sf::Event::Closed:
                window->close();
                break;
            // if user presses escape, end
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Escape)
                    window->close();
                break;
                // if user presses space to start and game has NOT started yet
                if (event.key.code == Keyboard::Space && gameState == startState) {
                    gameState = runState;
                }
                // if dino can jump, game has started, and space is pressed
                if (event.key.code == Keyboard::Space && gameState == runState && canJump()) {
                    jump(velocity.x,);
                }
            }
        }

        // Run Animation Dino Clock
        if(clock.getElapsedTime().asSeconds() > .1f) {
            // if animation is at end of sprite sheet start over
            if (dinoAnim.left == 336) {
                dinoAnim.left = 0;
            } else {
                // else get next frame
                dinoAnim.left += 24;
            }
            clock.restart();
        }



        // clear frame
        window->clear();

        /* Draw here */
        this->render();

        // display frame
        window->display();
    }
}



// actually don't think ill need this if since window is global var
// const sf::RenderTarget& Game::get_window() const {
//     return this->window;
// }

