#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
using namespace sf;

/* Constants */
const float GRAVITY = .75;
const float JUMPHEIGHT = 30;
const int WINDOWWIDTH = 1200;
const int WINDOWHEIGHT = 700;
const float JUMPSPEED = 20.0f;
const int GROUNDHEIGHT = 500;
const int TEXTLENGTH = 1472;

void bgWrap(RenderWindow &w, View &v, Sprite &sp1, Sprite &sp2)
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

    w.setView(v);
    w.draw(sp1);
    w.draw(sp2);
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

    /* Game variables */
    bool running = true;
    double runSpeed = 100;
    bool canJump = true;
    bool canJumpVar = true;
    float obsMoveSpeed = 8.f;
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
    tree.loadFromFile("../assets/tree2.png");
    Texture tree3;
    tree.loadFromFile("../assets/tree3.png");
    Texture tree4;
    tree.loadFromFile("../assets/tree4.png");
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
    treeSprite1.setPosition(WINDOWWIDTH + 200, GROUNDHEIGHT);

    Sprite treeSprite2(tree2);
    treeSprite2.setScale(2, 2);
    treeSprite2.setPosition(WINDOWWIDTH + 200, GROUNDHEIGHT);

    Sprite treeSprite3(tree3);
    treeSprite3.setScale(2, 2);
    treeSprite3.setPosition(WINDOWWIDTH + 200, GROUNDHEIGHT);

    Sprite treeSprite4(tree4);
    treeSprite4.setScale(2, 2);
    treeSprite4.setPosition(WINDOWWIDTH + 200, GROUNDHEIGHT);

    std::vector<Sprite> obstacles;

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
                break;
            default:
                break;
            }
        }

        bg1View.move(5.0f, 0);
        bg2View.move(1.0f, 0);
        bg3View.move(0.5f, 0);

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
        if (obsClock.getElapsedTime().asSeconds() > float(rand() % 2 + 1))
        {
            int randObsInt = rand() % 2;
            switch (randObsInt)
            {
            case 0:
                // tree
                obstacles.push_back(treeSprite1);
                break;
            case 1:
                obstacles.push_back(treeSprite3);
                break;
            case 2:
                obstacles.push_back(treeSprite4);
                break;
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
            if (!canJumpVar)
                dinoIntRect.left = 72;
            // Run Animation Dino Clock for each frame
            if (dinoClock.getElapsedTime().asSeconds() > float(8.0 / 60))
            {
                // if animation is at end of sprite sheet start over
                if (dino.getTextureRect().left == 216)
                    dinoIntRect.left = 96;
                else
                    // else get next frame
                    dinoIntRect.left += 24;
                if (!canJump)
                    dinoIntRect.left = 72;

                // set the dino sprite texture rect to the new frame
                dino.setTextureRect(dinoIntRect);
                dinoClock.restart();
                // set the dino sprite texture rect to the new frame
                dino.setTextureRect(dinoIntRect);
                dinoClock.restart();
            }

            // Update everything else 60 times a second
            if (frameClock.getElapsedTime().asSeconds() > float(1.0 / 60))
            {
                for (auto &obs : obstacles)
                {
                    // move obstacles down path
                    obs.move(-obsMoveSpeed, 0);

                    // if dino overlaps with obstacles
                    if (dino.getLocalBounds().intersects(obs.getLocalBounds()))
                    {
                        running = false;
                    }
                }
                frameClock.restart();
            }
        }

        // clear frame
        window.clear();

        /* Draw here */
        window.setView(mainView);
        window.draw(bg4);
        bgWrap(window, bg3View, bg3_1, bg3_2);
        bgWrap(window, bg2View, bg2_1, bg2_2);
        bgWrap(window, bg1View, bg1_1, bg1_2);
        window.setView(mainView);
        window.draw(dino);

        for (auto &obs : obstacles)
        {
            window.draw(obs);
        }

        // display frame
        window.display();
    }

    return 0;
}