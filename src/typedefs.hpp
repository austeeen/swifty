#ifndef TYPE_DEF_HPP
#define TYPE_DEF_HPP

#include <SFML/Graphics.hpp>
#include <map>
#include <memory>
#include <iomanip>
#include <iostream>
#include <string>

static const float FLT_ZERO = 0.1;
static const float STUCK_TIMEOUT = 5.f;

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

enum class Dir4 { up, down, left, right };

enum class ColliderType { generic, body, platform, immovable };

enum class ObjectState { idle, running, jumping, falling, healing, damaged, dead };

enum class RollState { none, next, done };

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

    const std::string asStr() const;
};

std::ostream& operator<<(std::ostream& o, const PhysicsCoeffs& u);

struct Waypoint {
    Waypoint(): loc(0, 0), next_id(-1), next(nullptr), prev(nullptr) {};
    Waypoint(sf::Vector2f l, int n_id): loc(l), next_id(n_id), next(nullptr), prev(nullptr) {};
    Waypoint(const Waypoint& o): loc(o.loc), next_id(o.next_id), next(o.next), prev(o.prev) {};
    Waypoint* setNext(Waypoint* n);
    sf::Vector2f loc;
    int next_id;
    Waypoint* next;
    Waypoint* prev;
};

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
