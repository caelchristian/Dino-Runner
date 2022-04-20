#include "SFML/Graphics.hpp"
#include "DinoGame.h"

int main()
{
    DinoGame game;
    while (game.isWindowOpen() && !(game.hasGameEnded())) {
        game.run();
    }
    return 0;
}
