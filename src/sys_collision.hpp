#ifndef COLLISION_HPP
#define COLLISION_HPP

#include "common.hpp"
#include "objects/boundary.hpp"
#include "objects/player.hpp"

struct CollisionEvent {
    std::shared_ptr<Boundary> colliding_object;
    CollisionGroup grp;
    ColliderType type;
    sf::Vector2f clipped_offset;
};

class CollisionSystem
{
public:
    CollisionSystem();
    void add(std::shared_ptr<Player> obj);
    void add(std::shared_ptr<Boundary> bnd);
    void checkCollisions();

private:
    const sf::Vector2f findIntersection(const sf::FloatRect& ra, const sf::FloatRect& rb) const;

    std::vector<CollisionEvent> collision_events;
    std::vector<std::shared_ptr<Boundary>> boundaries;
    std::vector<std::shared_ptr<Player>> objects;
};

#endif // COLLISION_HPP
