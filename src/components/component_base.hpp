#ifndef CMP_BASE_HPP
#define CMP_BASE_HPP

#include "../common.hpp"
#include "../rsrc_tiled.hpp"

class Player;
class GameObjectAsset;

class Component
{
public:
    Component(Player* obj);
    ~Component() { obj = nullptr; }
    virtual void build();
    virtual void setUp();
    virtual void update(const float dt);
    virtual void render(sf::RenderWindow &window);

public:
    Player* obj;
};

#endif // CMP_BASE_HPP
