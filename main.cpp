#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include <iostream>
using namespace std;
using namespace sf;

/* Constants */
const float GRAVITY = .75;
const float JUMPHEIGHT = 30;
const int WINDOWWIDTH = 1200;
const int WINDOWHEIGHT = 700;
const float JUMPSPEED = 20.0f;
const int GROUNDHEIGHT = 500;
const int TEXTLENGTH = 1472;
const float OBSMOVESPEED = 5.f;

void bgWrap(View &v, Sprite &sp1, Sprite &sp2)
{
    FloatRect bounds1 = sp1.getGlobalBounds();
    FloatRect bounds2 = sp2.getGlobalBounds();
    float viewX = v.getCenter().x;

    if (viewX > bounds1.left + bounds1.width / 2.0)
    {
        sp2.setPosition(bounds1.left + bounds1.width, bounds1.top);
    }
    if (viewX > bounds2.left + bounds2.width / 2.0)
    {
        sp1.setPosition(bounds2.left + bounds2.width, bounds2.top);
    }
}

void initBgSprite1(Sprite &sp)
{
    sp.setPosition(0, 0);
    sp.setScale(4, 4);
}

void initBgSprite2(Sprite &sp)
{
    sp.setPosition(TEXTLENGTH, 0);
    sp.setScale(4, 4);
}

int main()
{
    /* Window Variables */
    /* window is pointer to allow dynamic allocation in Game */
    VideoMode videoMode(WINDOWWIDTH, WINDOWHEIGHT);
    RenderWindow window(videoMode, "Dino Runner", Style::Close | Style::Titlebar);
    window.setFramerateLimit(60);
    Event event;
    Clock dinoClock;
    Clock obsClock;
    Clock frameClock;
    Font font;
    font.loadFromFile("../assets/Pixeboy-z8XGD.ttf");

    Text message;
    message.setFont(font);
    message.setString("Click Anywhere to Play Again!");
    message.setCharacterSize(90);
    message.setFillColor(sf::Color::Black);
    message.setPosition(WINDOWWIDTH / 2 - message.getLocalBounds().width / 2, WINDOWHEIGHT / 2 - message.getLocalBounds().height);

    /* Game variables */
    bool running = true;
    bool canJump = true;
    // IntRect params are (left,top,width,height)
    IntRect dinoIntRect = IntRect(72, 0, 24, 24);
    float velocity;

    View bg1View(Vector2f(WINDOWWIDTH / 2, WINDOWHEIGHT / 2), Vector2f(1200, 700));
    View bg2View(Vector2f(WINDOWWIDTH / 2, WINDOWHEIGHT / 2), Vector2f(1200, 700));
    View bg3View(Vector2f(WINDOWWIDTH / 2, WINDOWHEIGHT / 2), Vector2f(1200, 700));
    View mainView(Vector2f(WINDOWWIDTH / 2, WINDOWHEIGHT / 2), Vector2f(1200, 700));

    /* Textures */
    Texture tree;
    tree.loadFromFile("../assets/tree.png");
    Texture tree2;
    tree2.loadFromFile("../assets/tree2.png");
    Texture tree3;
    tree3.loadFromFile("../assets/tree3.png");
    Texture tree4;
    tree4.loadFromFile("../assets/tree4.png");
    Texture dinoText;
    dinoText.loadFromFile("../assets/green_dino.png");
    Texture bg1Text;
    bg1Text.loadFromFile("../assets/bg1.png");
    Texture bg2Text;
    bg2Text.loadFromFile("../assets/bg2.png");
    Texture bg3Text;
    bg3Text.loadFromFile("../assets/bg3.png");
    Texture bg4Text;
    bg4Text.loadFromFile("../assets/bg4.png");

    /* Sprites */

    Sprite dino(dinoText, dinoIntRect);
    // dino y position is 1st quadrant oriented
    dino.setPosition(100, 500);
    dino.setScale(5, 5);
    IntRect spriteSize(0, 0, WINDOWWIDTH, WINDOWHEIGHT);

    Sprite bg1_1(bg1Text);
    initBgSprite1(bg1_1);
    Sprite bg1_2(bg1Text);
    initBgSprite2(bg1_2);

    Sprite bg2_1(bg2Text);
    initBgSprite1(bg2_1);
    Sprite bg2_2(bg2Text);
    initBgSprite2(bg2_2);

    Sprite bg3_1(bg3Text);
    initBgSprite1(bg3_1);
    Sprite bg3_2(bg3Text);
    initBgSprite2(bg3_2);

    Sprite bg4(bg4Text);
    initBgSprite1(bg4);

    Sprite treeSprite1(tree);
    treeSprite1.setScale(2, 2);
    treeSprite1.setPosition(WINDOWWIDTH + 100, GROUNDHEIGHT);

    Sprite treeSprite2(tree2);
    treeSprite2.setScale(2, 2);
    treeSprite2.setPosition(WINDOWWIDTH + 100, GROUNDHEIGHT);

    Sprite treeSprite3(tree3);
    treeSprite3.setScale(2, 2);
    treeSprite3.setPosition(WINDOWWIDTH + 100, GROUNDHEIGHT);

    Sprite treeSprite4(tree4);
    treeSprite4.setScale(2, 2);
    treeSprite4.setPosition(WINDOWWIDTH + 100, GROUNDHEIGHT);

    vector<Sprite> obstacles;

    while (window.isOpen())
    {
        // poll to quit game
        while (window.pollEvent(event))
        {
            // if user closes window, end
            switch (event.type)
            {
            case Event::Closed:
                window.close();
                break;
                // if user presses escape, end
            case Event::KeyPressed:
                if (event.key.code == Keyboard::Escape)
                    window.close();
                if (event.key.code == Keyboard::Space && canJump)
                {
                    velocity = -JUMPSPEED;
                    canJump = false;
                }
                if (event.key.code == sf::Keyboard::G)
                {
                    dinoText.loadFromFile("../assets/green_dino.png");
                    dino.setTexture(dinoText);
                }
                if (event.key.code == sf::Keyboard::R)
                {
                    dinoText.loadFromFile("../assets/red_dino.png");
                    dino.setTexture(dinoText);
                }
                if (event.key.code == sf::Keyboard::Y)
                {
                    dinoText.loadFromFile("../assets/yellow_dino.png");
                    dino.setTexture(dinoText);
                }
                if (event.key.code == sf::Keyboard::B)
                {
                    dinoText.loadFromFile("../assets/blue_dino.png");
                    dino.setTexture(dinoText);
                }
                break;
            case Event::MouseButtonPressed:
                if (!running)
                {
                    obstacles.clear();
                    running = true;
                }
            default:
                break;
            }
        }

        if (running)
        {
            if (obstacles.size() > 10)
                obstacles.erase(obstacles.begin());

            bg1View.move(5.0f, 0);
            bg2View.move(1.0f, 0);
            bg3View.move(0.5f, 0);

            bgWrap(bg3View, bg3_1, bg3_2);
            bgWrap(bg2View, bg2_1, bg2_2);
            bgWrap(bg1View, bg1_1, bg1_2);

            // this->updateTerrain();
            // this->spawnObstacles();

            // store reference to Dino IntRect hitbox
            dino.move(0, velocity);

            // if the hitBox is below peak height, increase upwards velocity
            if (dino.getPosition().y + dino.getLocalBounds().height < GROUNDHEIGHT)
                velocity += GRAVITY;
            // else set position to ground height - hitBox height
            else
            {
                velocity = 0;
                dino.setPosition(dino.getPosition().x, GROUNDHEIGHT - dino.getLocalBounds().height);
                canJump = true;
            }

            // this->updateCollision();

            // Obstacle Clock
            if (obsClock.getElapsedTime().asSeconds() > float(rand() % 2 + 3))
            {
                int randObsInt = (rand() % static_cast<int>(3 + 1));
                switch (randObsInt)
                {
                case 0:
                    obstacles.push_back(treeSprite1);
                    break;
                case 1:
                    obstacles.push_back(treeSprite2);
                    break;
                case 2:
                    obstacles.push_back(treeSprite3);
                    break;
                case 3:
                    obstacles.push_back(treeSprite4);
                    break;
                default:
                    cerr << "UNREACHABLE!" << endl;
                }

                obsClock.restart();
            }

            // Run Animation Dino Clock for each frame
            if (dinoClock.getElapsedTime().asSeconds() > float(8.0 / 60))
            {
                // if animation is at end of sprite sheet start over
                if (dino.getTextureRect().left == 216)
                    dinoIntRect.left = 96;
                else
                    // else get next frame
                    dinoIntRect.left += 24;
                // jump anim
                if (!canJump)
                    dinoIntRect.left = 72;
                // set the dino sprite texture rect to the new frame
                dino.setTextureRect(dinoIntRect);
                dinoClock.restart();
            }

            // Update everything else 60 times a second
            for (auto &obs : obstacles)
            {
                // move obstacles down path
                obs.move(-OBSMOVESPEED, 0);
                FloatRect bounds = obs.getGlobalBounds();
                FloatRect smaller(bounds.left + 25, bounds.top, bounds.width - 40, bounds.height - 30);

                // if dino overlaps with obstacles
                if (dino.getGlobalBounds().intersects(smaller))
                    running = false;
            }
        }

        // clear frame
        window.clear();

        /* Draw here */
        window.setView(mainView);
        window.draw(bg4);

        window.setView(bg3View);
        window.draw(bg3_1);
        window.draw(bg3_2);

        window.setView(bg2View);
        window.draw(bg2_1);
        window.draw(bg2_2);

        window.setView(bg1View);
        window.draw(bg1_1);
        window.draw(bg1_2);

        window.setView(mainView);
        window.draw(dino);

        for (auto &obs : obstacles)
        {
            window.draw(obs);
        }

        if (!running)
            window.draw(message);

        // display frame
        window.display();
    }

    return 0;
}