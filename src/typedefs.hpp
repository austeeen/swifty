#ifndef TYPE_DEF_HPP
#define TYPE_DEF_HPP

#include <SFML/Graphics.hpp>
#include <map>
#include <memory>
#include <iomanip>

static const float FLT_ZERO = 0.1;

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

enum class Dir4 {up, down, left, right };

enum class ColliderType { generic, body, platform, immovable };

enum class ObjectState { idle, running, jumping, falling, wallsliding };

enum class RollState { none, next, done };

namespace out {
    const std::string toStr(const ObjectState s);
}

struct PhysicsCoeffs {
    static const int MASS_UNIT = 10;
    static const int SPEED_UNIT = 1;
    static const int VEL_UNIT = 5;
    static const int GRAV_UNIT = 1;
    static const int DAMP_UNIT = 1;
    static const int JUMP_UNIT = 1;
    enum class AsEnum { mass, speed, maxvel, gravity, damping, jump };

    PhysicsCoeffs();
    PhysicsCoeffs(const PhysicsCoeffs& other);

    int mass, speed, maxvel, jump, gravity, damping;
    void increase(const AsEnum n);
    void decrease(const AsEnum n);
};

std::ostream& operator<<(std::ostream& o, const PhysicsCoeffs& u);

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
