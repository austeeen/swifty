#include "devices.hpp"

InputDevice::InputDevice()
{}
io::state InputDevice::get(const io::binding b)
{
    // 00 == up - !cur.getBit( (int)b ) && !prev.getBit( (int)b );
    // 01 == released - return !cur.getBit( (int)b ) && prev.getBit( (int)b );
    // 10 == pressed - return cur.getBit( (int)b ) && !prev.getBit( (int)b );
    // 11 == down - return cur.getBit((int)b) && prev.getBit( (int)b );
    return (cur.getBit( (int)b ) << 1) + prev.getBit( (int)b );
}
Keyboard::Keyboard() : InputDevice()
{
    msg("Keyboard::Keyboard()", "Using Keyboard");
    this->bindings[io::left] = sf::Keyboard::Left;
    this->bindings[io::right] = sf::Keyboard::Right;
    this->bindings[io::down] = sf::Keyboard::Down;
    this->bindings[io::up] = sf::Keyboard::Up;
    this->bindings[io::select] = sf::Keyboard::Space;
    this->bindings[io::back] = sf::Keyboard::Q;
    this->bindings[io::menu] = sf::Keyboard::Z;
    this->bindings[io::quit] = sf::Keyboard::Escape;
}
void Keyboard::update()
{
    prev.setMask(cur);
    cur.setBit(io::left,   sf::Keyboard::isKeyPressed(bindings[io::left]));
    cur.setBit(io::right,  sf::Keyboard::isKeyPressed(bindings[io::right]));
    cur.setBit(io::up,     sf::Keyboard::isKeyPressed(bindings[io::up]));
    cur.setBit(io::down,   sf::Keyboard::isKeyPressed(bindings[io::down]));
    cur.setBit(io::select, sf::Keyboard::isKeyPressed(bindings[io::select]));
    cur.setBit(io::back,   sf::Keyboard::isKeyPressed(bindings[io::back]));
    cur.setBit(io::menu,   sf::Keyboard::isKeyPressed(bindings[io::menu]));
    cur.setBit(io::quit,   sf::Keyboard::isKeyPressed(bindings[io::quit]));
}
Joystick::Joystick(std::vector<int> cons) : InputDevice(),
joy_indx(-1), button_count(0), has_x(false), has_y(false), has_z(false), connections(cons)
{
    joy_indx = connections[0];
    button_count = sf::Joystick::getButtonCount(joy_indx);
    has_x = sf::Joystick::hasAxis(joy_indx, sf::Joystick::X);
    has_y = sf::Joystick::hasAxis(joy_indx, sf::Joystick::Y);
    has_z = sf::Joystick::hasAxis(joy_indx, sf::Joystick::Z);
    msg("Joystick::Joystick()", "Using Joystick [%d buttons, axis: (x:%d, y:%d, z:%d)]",
            button_count, has_x, has_y, has_z);
    this->bindings[io::select] = joy::snes::A;
    this->bindings[io::back] = joy::snes::B;
    this->bindings[io::menu] = joy::snes::ST;
    this->bindings[io::quit] = joy::snes::SL;
}
void Joystick::update()
{
    float x = sf::Joystick::getAxisPosition(joy_indx, sf::Joystick::X);
    float y = sf::Joystick::getAxisPosition(joy_indx, sf::Joystick::Y);
    prev.setMask(cur);
    cur.setBit(io::left,  x < 0);
    cur.setBit(io::right, x > 0);
    cur.setBit(io::down,  y > 0);
    cur.setBit(io::up,  y < 0);
    cur.setBit(io::select, sf::Joystick::isButtonPressed(joy_indx, bindings[io::select]));
    cur.setBit(io::back,   sf::Joystick::isButtonPressed(joy_indx, bindings[io::back]));
    cur.setBit(io::menu,   sf::Joystick::isButtonPressed(joy_indx, bindings[io::menu]));
    cur.setBit(io::quit,   sf::Joystick::isButtonPressed(joy_indx, bindings[io::quit]));
}
