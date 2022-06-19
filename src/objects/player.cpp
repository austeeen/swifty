#include "player.hpp"

Player::Player(const GameObjectAsset ast):
GameObject(CollisionGroup::object), ast(ast)
{
    /*
    states[ObjectState::idle] = std::make_unique<IdleState>(this);
    states[ObjectState::running] = std::make_unique<RunningState>(this);
    states[ObjectState::jumping] = std::make_unique<JumpingState>(this);
    states[ObjectState::falling] = std::make_unique<FallingState>(this);
    // states[ObjectState::wallsliding] = std::make_unique<WallSlidingState>(this);
    */

    cmpts[typeid(Sprite)] = std::make_shared<Sprite>(this);
    cmpts[typeid(RigidBody)] = std::make_shared<RigidBody>(this);
    cmpts[typeid(Animator)] = std::make_shared<Animator>(this);
}
void Player::setUp()
{
    for (auto [cmpnt_t, cmpnt] : cmpts) {
        cmpnt->build();
    }

    cur_state = ObjectState::idle;
    this->cmpnt<Animator>()->setState(cur_state);
    this->cmpnt<RigidBody>()->setState(cur_state);

    for (auto [cmpnt_t, cmpnt] : cmpts) {
        cmpnt->setUp();
    }
}
void Player::update(const float dt)
{
    ObjectState next = this->cmpnt<RigidBody>()->getState();
    if (next != cur_state) {
        // printf("%s -> %s\n", out::toStr(cur_state).c_str(), out::toStr(next).c_str());
        cur_state = next;
        this->cmpnt<Animator>()->setState(cur_state);
        this->cmpnt<RigidBody>()->setState(cur_state);
    }
    this->cmpnt<Animator>()->update(dt);
    this->cmpnt<RigidBody>()->update(dt);
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
            cmpnt<Sprite>()->setFacing(false);
            cmpnt<RigidBody>()->setDirection(dir);
            break;
        }
        case Dir4::right: {
            cmpnt<Sprite>()->setFacing(true);
            cmpnt<RigidBody>()->setDirection(dir);
            break;
        }
        default: break;
    }
}
void Player::stop(const Dir4 dir)
{
    cmpnt<RigidBody>()->stopDirection(dir);
}
void Player::jump()
{
    cmpnt<RigidBody>()->jump();
}
void Player::terminateJump()
{
    cmpnt<RigidBody>()->terminateJump();
    /*
    if(cmpnt<RigidBody>()->terminateJump()) {
        cmpnt<Animator>()->endEarly();
    }
    */
}
void Player::increase(const BodyPhysics cf)
{
    cmpnt<RigidBody>()->increase(cf);
}
void Player::decrease(const BodyPhysics cf)
{
    cmpnt<RigidBody>()->decrease(cf);
}
void Player::toggleRects()
{
    cmpnt<RigidBody>()->toggleDisplayBody();
}
const GameObjectAsset& Player::getAsset() const
{
    return this->ast;
}
const sf::Vector2f Player::getPosition() const
{
    return cmpnt<RigidBody>()->getPosition();
}
const sf::Vector2i Player::getSize() const
{
    return cmpnt<RigidBody>()->getSize();
}
const std::vector<CollisionRect>& Player::getRects() const
{
    return cmpnt<RigidBody>()->getRects();
}
