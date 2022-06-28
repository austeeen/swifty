#include "player.hpp"

Player::Player(const GameObjectAsset ast):
    GameObject(ast)
{}
void Player::setUp()
{
    for (auto [cmpnt_t, cmpnt] : cmpts) {
        cmpnt->build();
    }

    this->cmpnt<Animator>()->setState(cur_state);
    this->cmpnt<Physics2D>()->setState(cur_state);

    for (auto [cmpnt_t, cmpnt] : cmpts) {
        cmpnt->setUp();
    }
}
void Player::update(const float dt)
{
    this->cmpnt<Animator>()->update(dt);
    this->cmpnt<Physics2D>()->update(dt);
}
void Player::lateUpdate()
{
    ObjectState next = this->cmpnt<Physics2D>()->nextState();
    if (next != cur_state) {
        cur_state = next;
        this->cmpnt<Animator>()->setState(cur_state);
        this->cmpnt<Physics2D>()->setState(cur_state);
    }
}
void Player::render(sf::RenderWindow &window)
{
    for (auto [cmpnt_t, cmpnt] : cmpts) {
        cmpnt->render(window);
    }
}
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
    /*
    if(cmpnt<RigidBody>()->terminateJump()) {
        cmpnt<Animator>()->endEarly();
    }
    */
}
void Player::increase(const PhysicsCoeffs::AsEnum cf)
{
    cmpnt<Physics2D>()->increase(cf);
}
void Player::decrease(const PhysicsCoeffs::AsEnum cf)
{
    cmpnt<Physics2D>()->decrease(cf);
}
