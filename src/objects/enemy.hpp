#ifndef OBJ_ENEMY_HPP
#define OBJ_ENEMY_HPP

#include "game_object.hpp"

class Enemy: public KinematicObject
{
public:
    Enemy(const GameObjectAsset ast);
    void setUp() override;
    void update(const float dt) override;
    void lateUpdate() override;
    void render(sf::RenderWindow &window) override;
};


#endif // OBJ_ENEMY_HPP
