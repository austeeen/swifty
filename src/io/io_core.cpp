#include "io_core.hpp"

const char* io::str_bindings[] = { "left", "right", "down", "up", "select", "back", "menu", "quit" };
const char* io::str_states[] = { "idle", "released", "pressed", "down" };

bool joy::connected_joys(std::vector<int> &cons)
{
    sf::Joystick::update();
    for (int i = 0; i < joy::SFML_MAX_JOYS; i++) {
        if (sf::Joystick::isConnected(i)) {
            cons.push_back(i);
        }
    }
    return cons.size();
}
