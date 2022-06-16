#ifndef COLLISION_HPP
#define COLLISION_HPP

#include "common.hpp"
#include "game_object.hpp"

struct CollisionEvent {
    std::shared_ptr<GameObject> colliding_object;
    COLLIDER::group grp;
    ColliderType type;
    sf::Vector2f clipped_offset;
};

class CollisionSystem
{
public:
    CollisionSystem();
    void add(std::shared_ptr<GameObject> obj);
    void add(std::shared_ptr<Boundary> bnd);
    void checkCollisions();
    void handleCollisions();

private:
    void checkColliding(std::shared_ptr<GameObject> obj, std::shared_ptr<Boundary> bnd);
    sf::Vector2f clip(const sf::FloatRect& a, const sf::FloatRect& b);

    std::vector<CollisionEvent> collision_events;
    std::vector<std::shared_ptr<Boundary>> boundaries;
    std::vector<std::shared_ptr<GameObject>> objects;
};

#endif // COLLISION_HPP
