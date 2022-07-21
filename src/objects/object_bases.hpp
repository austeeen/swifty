#ifndef OBJ_BASES_HPP
#define OBJ_BASES_HPP

#include "../common.hpp"
#include "../assets.hpp"
#include "../components/all.hpp"

class ObjectBase
{
public:
    virtual ~ObjectBase() {};
    virtual void build() {};
    virtual void setUp() {};
    virtual void update(const float dt) {};
    virtual void lateUpdate() {};
    virtual void render(sf::RenderWindow &window) {};

    virtual void toggleDisplay() {};

protected:

};

class StaticObject : public ObjectBase
{
public:
    virtual const sf::FloatRect getCollider() const =0;

};

class DynamicObject : public ObjectBase
{
public:
    virtual const CollisionRect& getCollider() const =0;
    virtual const sf::Vector2f& getVelocity() const =0;
};


#endif // OBJ_BASES_HPP
