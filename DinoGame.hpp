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
    runState,
    pauseState,
};

class DinoGame
{
private:
    /* Window Variables */
    /* window is pointer to allow dynamic allocation in Game */
    RenderWindow *window;
    VideoMode videoMode;
    Event event;

    /* Game variables */
    GameState gameState;
    double runSpeed;
    std::vector<sf::RectangleShape> obstacles;
    bool canJumpVar;
    float jumpSpeed;
    int groundHeight;

    /* Textures */
    Texture dinoTexture;
    Texture bgTexture;
    Texture cactusTexture;

    /* Sprites */
    Sprite *bgSprite;
    Sprite *dinoSprite;
    Sprite *cactusSprite;

    /* Custom Objects */
    Dino dino;
    // vector<Obstacle> cacti;

    // IntRect params are (left,top,width,height)
    IntRect dinoIntRect = IntRect(0, 0, 24, 24);
    Vector2f velocity;

    /* Clock */
    Clock clock;

public:
    DinoGame();
    // ~DinoGame();

    /* Constants */
    const float GRAVITY = 3;
    const float JUMPHEIGHT = 30;
    const int WINDOWWIDTH = 800;
    const int WINDOWHEIGHT = 600;

    /* Status functions */
    const bool isWindowOpen();
    void pollEvents();

    /* Initializer functions */
    // void initWindow();
    void initVars();
    void initSprites();
    // void initText();
    void initClock();
    void initWindow();

    /* Accessors */
    const sf::RenderTarget &getWindow();
    // const bool canJump() const;

    /* Spawn functions */
    // void spawnObstacles();
    // void updateObstacles();
    //  void updatePlayer();
    // void updateGame();

    /* Update Functions */
    void updatePlayer();

    /* Draw functions
    void drawBackground();
    void drawPlayer();
    void drawObstacles(); */
    void render();

    void mainLoop();
    /*    const void jump(float yVelocity, float jumpHeight);
        void eventPoll();
        void repositionView(View &view);*/
};

#endif // M4OEP_CCHRIST7_QWARDEN_GAME_H
