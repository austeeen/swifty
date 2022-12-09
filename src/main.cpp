#include "game.hpp"


Logger::loglevel lvl = Logger::loglevel::err;

int main()
{
    // todo: add to settings.json
    Logger::setlvl(Logger::loglevel::dbg);
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
