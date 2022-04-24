#include <SFML/Graphics.hpp>
#include <memory>
using namespace sf;

/* Constants */
const float GRAVITY = 3;
const float JUMPHEIGHT = 30;
const int WINDOWWIDTH = 800;
const int WINDOWHEIGHT = 600;

int main()
{
    /* Window Variables */
    /* window is pointer to allow dynamic allocation in Game */
    VideoMode videoMode(WINDOWWIDTH, WINDOWHEIGHT);
    RenderWindow window(videoMode, "Dino Runner", sf::Style::Close | sf::Style::Titlebar);
    window.setFramerateLimit(60);
    Event event;
    Clock clock;

    /* Game variables */
    bool running = true;
    double runSpeed = 100;
    std::vector<sf::RectangleShape> obstacles;
    bool canJumpVar = true;
    float jumpSpeed = 20.0f;
    int groundHeight = 300;
    // IntRect params are (left,top,width,height)
    IntRect dinoIntRect = IntRect(72, 0, 24, 24);
    float velocity;

    /* Textures */
    Texture dinoTexture;
    dinoTexture.loadFromFile("../assets/green_dino.png");
    Texture ground;
    ground.loadFromFile("../assets/bg1.png");

    /* Sprites */

    Sprite dinoSprite(dinoTexture, dinoIntRect);
    dinoSprite.setPosition(WINDOWWIDTH / 6, WINDOWHEIGHT - WINDOWHEIGHT / 3);
    dinoSprite.setScale(5.f, 5.f);

    while (window.isOpen())
    {
        // poll to quit game
        while (window.pollEvent(event))
        {
            // if user closes window, end
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
                // if user presses escape, end
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Escape)
                    window.close();
                break;
            default:
                break;
            }
        }

        // this->updateTerrain();
        // this->spawnObstacles();

        // update dino position if jump
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && canJumpVar)
        {
            velocity = -jumpSpeed;
            running = true;
            canJumpVar = false;
        }

        // store reference to Dino IntRect hitbox
        dinoSprite.move(0, velocity);

        // if the hitBox is below peak height, increase upwards velocity
        if (dinoSprite.getPosition().y + dinoSprite.getLocalBounds().height < groundHeight)
            velocity += GRAVITY;
        // else set position to ground height - hitBox height
        else
        {
            velocity = 0;
            dinoSprite.setPosition(dinoSprite.getPosition().x, groundHeight - dinoSprite.getLocalBounds().height);
        }
        // if the hitBox is below peak height, increase upwards velocity
        if (dinoSprite.getPosition().y + dinoSprite.getLocalBounds().height < groundHeight || velocity < 0)
            velocity += GRAVITY;
        // else set position to ground height - hitBox height
        else
        {
            velocity = 0;
            dinoSprite.setPosition(dinoSprite.getPosition().x, groundHeight - dinoSprite.getLocalBounds().height);
            canJumpVar = true;
        }

        // this->updateCollision();

        // Run Animation Dino Clock for each frame
        if (clock.getElapsedTime().asSeconds() > float(8.0 / 60))
        {
            IntRect changeDinoRect;
            // if animation is at end of sprite sheet start over
            if (dinoSprite.getTextureRect().left == 216)
            {
                dinoIntRect.left = 96;
            }
            else
            {
                // else get next frame
                dinoIntRect.left += 24;
            }

            if (!canJumpVar)
            {
                dinoIntRect.left = 72;
            }

            // set the dino sprite texture rect to the new frame
            dinoSprite.setTextureRect(dinoIntRect);
            clock.restart();
        }

        // clear frame
        window.clear();

        /* Draw here */
        window.draw(dinoSprite);

        // display frame
        window.display();
    }

    return 0;
}