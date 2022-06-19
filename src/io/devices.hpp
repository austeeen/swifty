#ifndef IO_DEVICES_HPP
#define IO_DEVICES_HPP

#include "../common.hpp"
#include "../utils/bitmask.hpp"
#include "io_core.hpp"

class InputDevice
{
public:
    InputDevice();
    virtual ~InputDevice() {};
    virtual void update() = 0;
    io::state get(const io::binding b);

protected:
    Bitmask cur;
    Bitmask prev;
};

class Keyboard: public InputDevice
{
public:
    Keyboard();
    void update() override;
private:
    sf::Keyboard::Key bindings[io::NBINDS];
};

class Joystick : public InputDevice
{
public:
    Joystick(std::vector<int> cons);
    void update() override;

protected:
    int joy_indx;
    unsigned int button_count;
    bool has_x, has_y, has_z;

private:
    int bindings[io::NBINDS];
    std::vector<int> connections;
};

#endif // IO_DEVICES_HPP
