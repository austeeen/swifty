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
                const sf::Vector2f offset = findIntersection(obj_rect.aabb, bnd_aabb);
                if (fabs(offset.x) > 0.f && fabs(offset.y) > 0.f) {
                    obj->cmpnt<Physics2D>()->onColliding(offset, obj_rect.type);
                }
            }
        }
    }
}
const sf::Vector2f CollisionSystem::findIntersection(const sf::FloatRect& ra, const sf::FloatRect& rb) const
{
    const auto min = [](float a, float b) { return (a < b) ? a : b; };
    const auto max = [](float a, float b) { return (a < b) ? b : a; };

    const float left   = max(ra.left, rb.left);
    const float top    = max(ra.top,  rb.top);
    const float right  = min(ra.left + ra.width,  rb.left + rb.width);
    const float bottom = min(ra.top  + ra.height, rb.top  + rb.height);

    float dx = 0.0, dy = 0.0;
    if ((left < right) && (top < bottom)) {
        if (left == rb.left) { dx = left - right; }
        else { dx = right - left; }
        if (top == rb.top) { dy = top - bottom; }
        else { dy = bottom - top; }
    }
    return sf::Vector2f(dx, dy);
}
