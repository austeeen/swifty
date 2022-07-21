#include "game_manager.hpp"

int main()
{
    GameManager game;
    game.setUp();
    game.render();
    while (game.isRunning()) {
        game.update();
        game.render();
    }
    game.exit();

    return 0;
}
