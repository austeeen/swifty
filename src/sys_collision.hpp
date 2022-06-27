#ifndef COLLISION_HPP
#define COLLISION_HPP

#include "common.hpp"
#include "objects/boundary.hpp"
#include "objects/player.hpp"


class CollisionSystem
{
public:
    CollisionSystem();
    void add(std::shared_ptr<StaticObject> obj);
    void add(std::shared_ptr<DynamicObject> obj);
    void add(std::shared_ptr<KinematicObject> obj);
    void checkCollisions();

private:
    void vsKinematicObjects(std::shared_ptr<KinematicObject> kin_obj);
    void vsDynamicObjects(std::shared_ptr<KinematicObject> kin_obj);
    void vsStaticObjects(std::shared_ptr<KinematicObject> kin_obj);

    const sf::Vector2f findIntersection(const sf::FloatRect& ra, const sf::FloatRect& rb) const;

    std::vector<std::shared_ptr<StaticObject>> static_objs;
    std::vector<std::shared_ptr<DynamicObject>> dyn_objs;
    std::vector<std::shared_ptr<KinematicObject>> kin_objs;
};

#endif // COLLISION_HPP
