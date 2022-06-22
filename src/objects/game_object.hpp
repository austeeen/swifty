#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include "../common.hpp"
#include "../assets.hpp"
#include "../components/all.hpp"

class ComponentType
{
public:
    template <typename T> std::shared_ptr<T> cmpnt() const {
        if (cmpts.count(typeid(T)) == 0)
            return nullptr;
        return std::dynamic_pointer_cast<T>(cmpts.at(typeid(T)));
    }
protected:
    std::map<std::type_index, std::shared_ptr<Component>> cmpts;
};

class GameObjectBase
{
public:
    virtual void setUp() {};
    virtual void update(const float dt) {};
    virtual void lateUpdate() {};
    virtual void render(sf::RenderWindow &window) {};
};

class StaticObject : public GameObjectBase
{
public:
    virtual const sf::FloatRect getCollider() const =0;

};

class DynamicObject : public GameObjectBase
{
public:
    virtual const CollisionRect& getCollider() const =0;

};

class KinematicObject : public GameObjectBase, public ComponentType
{
public:

};

#endif // GAMEOBJECT_HPP
