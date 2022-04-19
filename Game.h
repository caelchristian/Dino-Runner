//
// Created by Cael Christian on 4/19/22.
//

#ifndef M4OEP_CCHRIST7_QWARDEN_GAME_H
#define M4OEP_CCHRIST7_QWARDEN_GAME_H
#include <SFML/Graphics.hpp>


class Game {
private:
    /* Window Variables */
    sf::RenderWindow window;
    sf::VideoMode videoMode;
    sf::Event ev;

    /* Game variables */
    int health;
    std::vector<sf::RectangleShape> obstacles;
    const float GRAVITY = 9.81;

    /* Initializer functions */
    void init_window();
    void init_variables();
    void init_sprites();
    void init_text();
    void init();
public:
    Game();
    ~Game();
    /* Status functions */
    const bool is_window_open();
    const bool has_game_ended();

    /* Accessors */
    const sf::RenderTarget& get_window() const;

    /* Spawn functions */
    void spawn_obstacles();
    void update_obstacles();
    void update_game();

    /* Draw functions */
    void draw_player();
    void draw_obstacles();
    void draw();

};


#endif //M4OEP_CCHRIST7_QWARDEN_GAME_H
