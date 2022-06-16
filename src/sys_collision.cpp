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
void CollisionSystem::handleCollisions()
{
    for (auto& evt : collision_events) {
        evt.colliding_object->onColliding(evt.grp, evt.type, evt.clipped_offset);
    }
    collision_events.clear();
}
void CollisionSystem::checkColliding(std::shared_ptr<GameObject> obj, std::shared_ptr<Boundary> bnd)
{
    const std::vector<CollisionRect> object_rects = obj->getRects();
    sf::FloatRect bnd_rect = bnd->getRect();

    for (auto& obj_rect : object_rects) {
        if (obj_rect.rect.intersects(bnd_rect)) {
            collision_events.push_back(CollisionEvent{
                obj, bnd->getColliderGroup(), obj_rect.type, clip(obj_rect.rect, bnd_rect)
            });
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
