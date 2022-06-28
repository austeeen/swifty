#ifndef OBJ_PLAYER_HPP
#define OBJ_PLAYER_HPP

#include "game_object.hpp"

class Player: public GameObject
{
public:
    Player(const GameObjectAsset ast);
    void setUp() override;
    void update(const float dt) override;
    void lateUpdate() override;
    void render(sf::RenderWindow &window) override;

    void move(const Dir4);
    void stop(const Dir4);
    void jump();
    void terminateJump();

    void increase(const PhysicsCoeffs::AsEnum cf);
    void decrease(const PhysicsCoeffs::AsEnum cf);
};


#endif // OBJ_PLAYER_HPP
