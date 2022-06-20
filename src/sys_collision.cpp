#include "sys_collision.hpp"

CollisionSystem::CollisionSystem()
{}
void CollisionSystem::add(std::shared_ptr<Player> obj)
{
    objects.push_back(obj);
}
void CollisionSystem::add(std::shared_ptr<Boundary> bnd)
{
    boundaries.push_back(bnd);
}
void CollisionSystem::checkCollisions()
{
    for (auto& obj : objects) {
        for (auto& bnd : boundaries) {
            sf::FloatRect bnd_aabb = bnd->getRect();
            for (auto& obj_rect : obj->cmpnt<RigidBody>()->getRects()) {
                if (obj_rect.aabb.intersects(bnd_aabb)) {
                    obj->cmpnt<Physics2D>()->onColliding(clip(obj_rect.aabb, bnd_aabb), obj_rect.type);
                }
            }
        }
    }
}
sf::Vector2f CollisionSystem::clip(const sf::FloatRect &a, const sf::FloatRect &b)
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
