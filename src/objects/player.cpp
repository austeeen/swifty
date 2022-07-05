#include "player.hpp"

Player::Player(const GameObjectAsset ast):
    GameObject(ast)
{}
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
