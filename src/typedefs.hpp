#ifndef TYPE_DEF_HPP
#define TYPE_DEF_HPP

#include <SFML/Graphics.hpp>
#include <map>
#include <memory>
// #include "rect.hpp"

static const float FLT_ZERO = 0.1;

enum class Dir4 {up, down, left, right };

enum class CollisionGroup { none, floor, object };
enum class ColliderType { generic, body };

enum class BodyPhysics { mass, speed, max_x_vel, gravity, damping, jump_power };

enum class ObjectState { idle, running, jumping, falling, wallsliding };

enum class RollState { none, next, done };

namespace out {
    const std::string toStr(const ObjectState s);
}

struct CollisionRect {
    sf::Vector2f offset;
    sf::FloatRect aabb;
    ColliderType type;
};

struct TileFrame {
    int gid;
    sf::IntRect texture_rect;
    std::vector<CollisionRect> collision_rects;
    float duration;
};

struct AnimRoll {
    std::vector<std::shared_ptr<TileFrame>> frames;
    bool one_shot = false;
    bool hold_last_frame = false;
    int end_early_frame = 0;
};

#endif // TYPE_DEF_HPP
