#include <tclap/CmdLine.h>
#include "game.hpp"


Logger::loglevel lvl = Logger::loglevel::err;
std::map<std::string, Logger::loglevel> Logger::str2log {
    {"debug", Logger::loglevel::dbg},
    {"message", Logger::loglevel::msg},
    {"warning", Logger::loglevel::wrn},
    {"error", Logger::loglevel::err},
};

int main(int argc, char** argv)
{

    try {  

        TCLAP::CmdLine game_args("Swifty. A game about a cat.", ' ', "0.0.1");

        std::vector<std::string> loglevel_keys;
		for (auto& [key, lvl] : Logger::str2log) {
            loglevel_keys.push_back(key);
        }
        TCLAP::ValuesConstraint<std::string> allowed_loglvls(loglevel_keys);

        TCLAP::ValueArg<std::string> loglevel_arg(
            "l", "log-level", "Set the log level", false, "debug", &allowed_loglvls);

        game_args.add(loglevel_arg);
        game_args.parse(argc, argv);
        
        Logger::setlvl(Logger::str2log.at(loglevel_arg.getValue()));
	
    } catch (TCLAP::ArgException &e) { 
        std::cerr << "error: " << e.error() << " for arg " << e.argId() << std::endl; 
        return 0;
    }

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
