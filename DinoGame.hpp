//
// Created by Cael Christian on 4/19/22.
//

#ifndef M4OEP_CCHRIST7_QWARDEN_DINOGAME_H
#define M4OEP_CCHRIST7_QWARDEN_DINOGAME_H

#include <SFML/Graphics.hpp>
#include "Dino.hpp"

#include <iostream>
#include <vector>
#include <string>

using namespace sf;

enum GameState
{
    startState,
    runState,
    pauseState,
    endState
};
class DinoGame
{
private:
    /* Window Variables */
    /* window is pointer to allow dynamic allocation in Game */
    sf::RenderWindow *window;
    sf::VideoMode videoMode;
    sf::Event event;

    /* Game variables */
    int health;
    double runSpeed;
    std::vector<sf::RectangleShape> obstacles;
    bool canJumpVar;
    static GameState gameState;

    /* Textures */
    Texture bgTexture;
    Texture dinoTexture;
    Texture cactusTexture;

    /* Sprites */
    Sprite *bgSprite;
    Sprite *dinoSprite;
    Sprite *cactusSprite;

    IntRect dinoAnim = IntRect(0, 0, 24, 24);

    /* Clock */
    Clock clock;

    /* Initializer functions */
    void initWindow();
    void initVars();
    void initSprites();
    void initText();
    void initClock();
    void init();

public:
    DinoGame();
    // ~DinoGame();

    /* Constants */
    const float GRAVITY = 9.81;
    const float JUMPHEIGHT = 30;
    const int WINDOWWIDTH = 800;
    const int WINDOWHEIGHT = 600;

    /* Status functions */
    const bool isWindowOpen();
    const bool hasGameEnded();

    /* Accessors */
    const sf::RenderTarget &get_window() const;
    const bool canJump() const;

    /* Spawn functions */
    void spawnObstacles();
    void updateObstacles();
    void updateGame();

    /* Draw functions */
    void drawPlayer();
    void drawObstacles();
    void drawBackground();
    void render();

    void run();
    const void jump(float yVelocity);
    void eventPoll();
    void repositionView(View &view);
};

#endif // M4OEP_CCHRIST7_QWARDEN_GAME_H
