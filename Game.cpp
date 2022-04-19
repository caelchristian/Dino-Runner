//
// Created by Cael Christian on 4/19/22.
//

#include "Game.h"

Game::Game() {
    void init();

}

void Game::init() {
    // initialize window
    this->videoMode = sf::VideoMode(800, 600);
	this->window = new sf::RenderWindow(this->videoMode, "Geometry Dash/Dino Game????", sf::Style::Close | sf::Style::Titlebar);
	this->window->setFramerateLimit(60);

    // TODO: initialize variables


    // TODO: initialize sprites/shapes


    // TODO: Initialize Text 
}

const bool Game::hasGameEnded() {
    this->window->isOpen();
}


void Game::render() {
    for (auto& o : obstacles) {
        this->window->draw(o);
    }
    // this->window->draw(player);
}

void Game::run() {
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
            if (event.key.code == sf::Keyboard::Escape) {
                window->close();
            }
        break;
        }
    }

    // clear frame
    window->clear();

    /* Draw here */
    this->render();

    // display frame
    window->display();
}


// actually don't think ill need this if since window is global var
// const sf::RenderTarget& Game::get_window() const {
//     return this->window;
// }

