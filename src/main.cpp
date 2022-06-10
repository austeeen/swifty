#include "game.hpp"

int main()
{
    Game game;
    game.setUp();
    game.render();
    while (game.isRunning()) {
        game.update();
        game.render();
    }

    return 0;
}
