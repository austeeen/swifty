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
    checked_this_frame.clear();
    collided_already.clear();
    for (auto& kin : kin_objs) {
        vsKinematicObjects(kin);
        vsDynamicObjects(kin);
        vsStaticObjects(kin);
    }
}
void CollisionSystem::vsKinematicObjects(std::shared_ptr<KinematicObject> kin_objA)
{
    const std::string objA_name = kin_objA->getName();
    for (auto& kin_objB : kin_objs)
    {
        const std::string objB_name = kin_objB->getName();
        if (objA_name == objB_name) {
            continue;
        }
        // (B, A) not (A, B)
        std::pair<std::string, std::string> collision_pair(objB_name, objA_name);
        if (checked_this_frame.count(collision_pair) != 0) {
            continue;
        }
        checked_this_frame.insert(collision_pair);


        /*
        for (auto& objA_col : kin_objA->cmpnt<RigidBody>()->getColliders())
        {
            for (auto& objB_col : kin_objB->cmpnt<RigidBody>()->getColliders())
            {
                // handle kinematic collisions

                const sf::Vector2f offset = findIntersection(objA_col.aabb, objB_col.aabb);
                if (fabs(offset.x) > 0.f && fabs(offset.y) > 0.f) {
                    kin_objA->cmpnt<Physics2D>()->onColliding(offset, objB_col.type, objA_col.type);
                    kin_objA->cmpnt<Physics2D>()->updateInertia(kin_objB->cmpnt<Physics2D>()->getVelocity());
                    checked_this_frame.insert(collision_pair);
                    break;
                }
            }
        }
        */
    }
}
void CollisionSystem::vsDynamicObjects(std::shared_ptr<KinematicObject> kin_obj)
{
    for (auto& dyn_obj : dyn_objs) {
        for (auto& obj_rect : kin_obj->cmpnt<RigidBody>()->getColliders()) {
            const CollisionRect d_col = dyn_obj->getCollider();
            const sf::Vector2f offset = findIntersection(obj_rect.aabb, d_col.aabb);
            if (fabs(offset.x) > 0.f && fabs(offset.y) > 0.f) {
                kin_obj->cmpnt<Physics2D>()->onColliding(offset, d_col.type, obj_rect.type);
                kin_obj->cmpnt<Physics2D>()->updateInertia(dyn_obj->getVelocity());
            }
        }
    }
}
void CollisionSystem::vsStaticObjects(std::shared_ptr<KinematicObject> kin_obj)
{
    for (auto& stat : static_objs) {
        for (auto& obj_rect : kin_obj->cmpnt<RigidBody>()->getColliders()) {
            const sf::Vector2f offset = findIntersection(obj_rect.aabb, stat->getCollider());
            if (fabs(offset.x) > 0.f && fabs(offset.y) > 0.f) {
                kin_obj->cmpnt<Physics2D>()->onColliding(offset, ColliderType::immovable, obj_rect.type);
                kin_obj->cmpnt<Physics2D>()->updateInertia(sf::Vector2f(0.f, 0.f));
            }
        }
    }
}
const sf::Vector2f CollisionSystem::findIntersection(const sf::FloatRect& ra, const sf::FloatRect& rb) const
{
    const auto min = [](const float a, const float b) { return (a < b) ? a : b; };
    const auto max = [](const float a, const float b) { return (a < b) ? b : a; };

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
