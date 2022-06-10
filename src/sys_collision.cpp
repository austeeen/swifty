#include "sys_collision.hpp"

CollisionSystem::CollisionSystem()
{}
void CollisionSystem::add(std::shared_ptr<GameObject> obj)
{
    objects.push_back(obj);
}
void CollisionSystem::add(std::shared_ptr<Boundary> bnd)
{
    boundaries.push_back(bnd);
}
void CollisionSystem::checkCollisions()
{
    for (auto& bnd : boundaries) {
        for (auto& obj : objects) {
            checkColliding(obj, bnd);
        }
    }
}
void CollisionSystem::checkColliding(std::shared_ptr<GameObject> obj, std::shared_ptr<Boundary> bnd)
{
    sf::FloatRect objRect = obj->getRect();
    sf::FloatRect bndRect = bnd->getRect();

    if (objRect.intersects(bndRect)) {
        obj->onColliding(bnd->getColliderGroup(), clip(objRect, bndRect));
    }
}
sf::Vector2f CollisionSystem::clip(sf::FloatRect &a, sf::FloatRect &b)
{
    float dx = 0.0, dy = 0.0;

    if (b.left > a.left) {
        dx = b.left - (a.left + a.width); // dy < 0
    } else {
        dx = (b.left + b.width) - a.left; // dx > 0
    }
    if (b.top > a.top) {
        dy = b.top - (a.top + a.height); // dy < 0
    } else {
        dy = (b.top + b.height) - a.top; // dy > 0
    }
    return sf::Vector2f(dx, dy);
}
