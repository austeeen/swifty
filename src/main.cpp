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
    game.exit();

    return 0;
}
