#ifndef CMP_BASE_HPP
#define CMP_BASE_HPP

#include "../common.hpp"

class KinematicObject;
class GameObjectAsset;

class Component
{
public:
    Component(KinematicObject* obj);
    ~Component() { obj = nullptr; }
    virtual void build();
    virtual void setUp();
    virtual void update(const float dt);
    virtual void render(sf::RenderWindow &window);

public:
    KinematicObject* obj;
};

#endif // CMP_BASE_HPP
