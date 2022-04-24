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
    std::shared_ptr<RenderWindow> window = std::make_shared<RenderWindow>(videoMode, "Dino Game", sf::Style::Close | sf::Style::Titlebar);
    window->setFramerateLimit(60);
    Event event;
    Clock clock;

    /* Game variables */
    bool running = true;
    double runSpeed = 100;
    std::vector<sf::RectangleShape> obstacles;
    bool canJumpVar = true;
    float jumpSpeed = 3.0f;
    int groundHeight = 300;
    // IntRect params are (left,top,width,height)
    IntRect dinoIntRect = IntRect(0, 0, 24, 24);
    Vector2f velocity;

    /* Textures */
    Texture dinoTexture;
    dinoTexture.loadFromFile("../assets/dinos/green_dino.png");
    Texture ground;
    ground.loadFromFile("../assets/bg1.png");

    /* Sprites */

    Sprite dinoSprite(dinoTexture,dinoIntRect);
    dinoSprite.setPosition(WINDOWWIDTH/6,WINDOWHEIGHT - WINDOWHEIGHT/3);
    dinoSprite.setScale(5.f,5.f);


    while (window->isOpen())
    {
        // poll to quit game
        while (window->pollEvent(event))
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

        // this->updateTerrain();
        // this->spawnObstacles();

        // update dino position if jump
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            velocity.x = jumpSpeed;
            running = true;
        }

//        // store reference to Dino IntRect hitbox
//        RectangleShape hitBox = dino.getHitBox();
//        hitBox.move(velocity.x, velocity.y);
//
//        // if the hitBox is below peak height, increase upwards velocity
//        if (hitBox.getPosition().y + hitBox.getSize().y < groundHeight)
//            velocity.y += GRAVITY;
//            // else set position to ground height - hitBox height
//        else
//        {
//            velocity.y = 0;
//            hitBox.setPosition(hitBox.getPosition().x, groundHeight - hitBox.getSize().y);
//        }
//        // if the hitBox is below peak height, increase upwards velocity
//        if (hitBox.getPosition().y + hitBox.getSize().y < groundHeight)
//            velocity.y += GRAVITY;
//        // else set position to ground height - hitBox height
//        else
//        {
//            velocity.y = 0;
//            hitBox.setPosition(hitBox.getPosition().x, groundHeight - hitBox.getSize().y);
//        }

        // this->updateCollision();


        // Run Animation Dino Clock
        if (clock.getElapsedTime().asSeconds() > .1f)
        {
            //dino.nextFrame(dinoIntRect);
            clock.restart();
        }

        // clear frame
        window->clear();

        /* Draw here */
        window->draw(dinoSprite);

        // display frame
        window->display();
    }

    return 0;
}