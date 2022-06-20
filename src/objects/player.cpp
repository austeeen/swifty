#include "player.hpp"

Player::Player(const GameObjectAsset ast):
GameObject(CollisionGroup::object), ast(ast), cur_state(ObjectState::idle)
{
    /*
    states[ObjectState::idle] = std::make_unique<IdleState>(this);
    states[ObjectState::running] = std::make_unique<RunningState>(this);
    states[ObjectState::jumping] = std::make_unique<JumpingState>(this);
    states[ObjectState::falling] = std::make_unique<FallingState>(this);
    // states[ObjectState::wallsliding] = std::make_unique<WallSlidingState>(this);
    */

    cmpts[typeid(Sprite)] = std::make_shared<Sprite>(this);
    cmpts[typeid(Physics2D)] = std::make_shared<Physics2D>(this);
    cmpts[typeid(RigidBody)] = std::make_shared<RigidBody>(this);
    cmpts[typeid(Animator)] = std::make_shared<Animator>(this);
}
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
    ObjectState next = this->cmpnt<Physics2D>()->getState();
    if (next != cur_state) {
        // printf("%s -> %s\n", out::toStr(cur_state).c_str(), out::toStr(next).c_str());
        cur_state = next;
        this->cmpnt<Animator>()->setState(cur_state);
        this->cmpnt<Physics2D>()->setState(cur_state);
    }
    this->cmpnt<Animator>()->update(dt);
    this->cmpnt<Physics2D>()->update(dt);
}
void Player::lateUpdate()
{

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
void Player::toggleRects()
{
    cmpnt<RigidBody>()->toggleDisplay();
}
const GameObjectAsset& Player::getAsset() const
{
    return this->ast;
}
