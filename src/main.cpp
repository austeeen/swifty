#include <tclap/CmdLine.h>
#include "game.hpp"

#define DEFAULT_FPS 60

Logger::loglevel lvl = Logger::loglevel::err;
std::map<std::string, Logger::loglevel> Logger::str2log {
    {"debug", Logger::loglevel::dbg},
    {"message", Logger::loglevel::msg},
    {"warning", Logger::loglevel::wrn},
    {"error", Logger::loglevel::err},
};

int main(int argc, char** argv)
{
    int fps = DEFAULT_FPS;
    bool rects_on = false;
    bool wait_per_frame = false;

    try {

        TCLAP::CmdLine game_args("Swifty. A game about a cat.", ' ', "0.0.1");

        std::vector<std::string> loglevel_keys;
		for (auto& [key, lvl] : Logger::str2log) {
            loglevel_keys.push_back(key);
        }
        TCLAP::ValuesConstraint<std::string> allowed_loglvls(loglevel_keys);

        TCLAP::ValueArg<std::string> loglevel_arg(
            "l", "log-level", "Set the log level", 
            false, "debug", &allowed_loglvls
        );
        TCLAP::ValueArg<int> fps_arg(
            "f",  "fps", "Set the max FPS",
            false, DEFAULT_FPS, "integer"
        );
        TCLAP::SwitchArg rects_on_arg(
            "r", "rects-on", "Show collision/animation rects"
        );
        TCLAP::SwitchArg wait_per_frame_arg(
            "w", "wait-per-frame", "Halt after each frame, use 'n' to move forward"
        );

        game_args.add(loglevel_arg);
        game_args.add(fps_arg);
        game_args.add(rects_on_arg);
        game_args.add(wait_per_frame_arg);

        game_args.parse(argc, argv);
        
        Logger::setlvl(Logger::str2log.at(loglevel_arg.getValue()));

        fps = fps_arg.getValue();
        rects_on = rects_on_arg.getValue();
        wait_per_frame = wait_per_frame_arg.getValue();
	
    } catch (TCLAP::ArgException &e) { 
        std::cerr << "error: " << e.error() << " for arg " << e.argId() << std::endl; 
        return 0;
    }

    Game game(fps, rects_on, wait_per_frame);
    game.setUp();
    game.render();
    while (game.isRunning()) {
        game.update();
        game.render();
    }
    game.exit();

    return 0;
}
