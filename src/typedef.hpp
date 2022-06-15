#ifndef TYPE_DEF_HPP
#define TYPE_DEF_HPP

#include <SFML/Graphics.hpp>

#define DIR_UP 0
#define DIR_DOWN 1
#define DIR_LEFT 2
#define DIR_RIGHT 3

namespace COLLIDER
{
    enum class group {
        none, floor, object
    };
}

enum class BodyPhysics { mass, speed, max_x_vel, gravity, damping, jump_power };
enum class BodyState { grounded, in_air };

#endif // TYPE_DEF_HPP
