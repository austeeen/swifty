#ifndef COLLISION_HPP
#define COLLISION_HPP

#include "common.hpp"
#include "game_object.hpp"

class CollisionSystem
{
public:
    CollisionSystem();
    void add(std::shared_ptr<GameObject> obj);
    void add(std::shared_ptr<Boundary> bnd);
    void checkCollisions();

private:
    void checkColliding(std::shared_ptr<GameObject> obj, std::shared_ptr<Boundary> bnd);
    sf::Vector2f clip(sf::FloatRect& a, sf::FloatRect& b);

    std::vector<std::shared_ptr<Boundary>> boundaries;
    std::vector<std::shared_ptr<GameObject>> objects;
};

#endif // COLLISION_HPP
