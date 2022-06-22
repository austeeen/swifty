#include "sys_collision.hpp"

CollisionSystem::CollisionSystem()
{}
void CollisionSystem::add(std::shared_ptr<StaticObject> obj)
{
    static_objs.push_back(obj);
}
void CollisionSystem::add(std::shared_ptr<DynamicObject> obj)
{
    dyn_objs.push_back(obj);
}
void CollisionSystem::add(std::shared_ptr<KinematicObject> obj)
{
    kin_objs.push_back(obj);
}
void CollisionSystem::checkCollisions()
{
    for (auto& kin : kin_objs) {
        for (auto& stat : static_objs) {
            for (auto& obj_rect : kin->cmpnt<RigidBody>()->getRects()) {
                const sf::Vector2f offset = findIntersection(obj_rect.aabb, stat->getCollider());
                if (fabs(offset.x) > 0.f && fabs(offset.y) > 0.f) {
                    kin->cmpnt<Physics2D>()->onColliding(offset, obj_rect.type);
                }
            }
        }
    }
}
const sf::Vector2f CollisionSystem::findIntersection(const sf::FloatRect& ra, const sf::FloatRect& rb) const
{
    const float min = [](const float a, const float b) { return (a < b) ? a : b; };
    const float max = [](const float a, const float b) { return (a < b) ? b : a; };

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
