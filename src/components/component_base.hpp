#ifndef CMP_BASE_HPP
#define CMP_BASE_HPP

#include "../common.hpp"

class GameObject;
class GameObjectAsset;

class Component
{
public:
    Component(GameObject* obj);
    ~Component() { obj = nullptr; }
    virtual void build();
    virtual void setUp();
    virtual void update(const float dt);
    virtual void render(sf::RenderWindow &window);

public:
    GameObject* obj;
};

#endif // CMP_BASE_HPP
