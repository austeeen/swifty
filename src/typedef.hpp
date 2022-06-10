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

namespace PHY
{
    const int mass = 0;
    const int speed = 1;
    const int max_x_vel = 2;
    const int gravity = 3;
    const int friction = 4;
    const int jump_power = 5;
    enum class stateID { grounded, in_air };

}

struct animconfig {
    int row, num_frames;
    float dur;
    std::vector<int> frames;
    bool one_shot = false;
    bool hold_last_frame = false;
    int end_early_frame = 0;
    // std::vector<int> repeat_frames;
    // int repeat_count = 0;
};

#endif // TYPE_DEF_HPP
