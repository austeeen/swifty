#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include "../common.hpp"

class GameObject
{
public:
    GameObject(const CollisionGroup grp);
    virtual void setUp() {};
    virtual void update(const float dt) {};
    virtual void lateUpdate() {};
    virtual void render(sf::RenderWindow &window) {};
    const CollisionGroup getColliderGroup() const { return col_group; };

protected:
    const CollisionGroup col_group;
};


#endif // GAMEOBJECT_HPP
