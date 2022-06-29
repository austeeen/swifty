#include "player.hpp"

Player::Player(const GameObjectAsset ast):
    GameObject(ast)
{}
void Player::move(const Dir4 dir)
{
    switch(dir) {
        case Dir4::left: {
            cmpnt<Physics2D>()->setMoving(dir);
            cmpnt<Sprite>()->setFacing(false);
            cmpnt<RigidBody>()->updateFacing(dir);
            break;
        }
        case Dir4::right: {
            cmpnt<Physics2D>()->setMoving(dir);
            cmpnt<Sprite>()->setFacing(true);
            cmpnt<RigidBody>()->updateFacing(dir);
            break;
        }
        default: break;
    }
}
void Player::stop(const Dir4 dir)
{
    cmpnt<Physics2D>()->stopMoving(dir);
}
void Player::jump()
{
    cmpnt<Physics2D>()->jump();
}
void Player::terminateJump()
{
    cmpnt<Physics2D>()->terminateJump();
}
void Player::increase(const PhysicsCoeffs::AsEnum cf)
{
    cmpnt<Physics2D>()->increase(cf);
}
void Player::decrease(const PhysicsCoeffs::AsEnum cf)
{
    cmpnt<Physics2D>()->decrease(cf);
}
