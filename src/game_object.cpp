#include "game_object.hpp"

GameObject::GameObject(const GameObjectAsset ast):
col_group(COLLIDER::group::object), ast(ast)
{
    cmpts[typeid(Sprite)] = std::make_shared<Sprite>(this);
    cmpts[typeid(Animator)] = std::make_shared<Animator>(this);
    cmpts[typeid(RigidBody)] = std::make_shared<RigidBody>(this);
}
void GameObject::setUp()
{
    for (auto [cmpnt_t, cmpnt] : cmpts) {
        cmpnt->setUp();
    }
}
void GameObject::jump()
{
    cmpnt<RigidBody>()->jump();
}
void GameObject::terminateJump()
{
    /*
    if(cmpnt<RigidBody>()->terminateJump()) {
        cmpnt<Animator>()->endEarly();
    }
    */
}
void GameObject::moving(const int dir)
{
    switch(dir) {
        case DIR_LEFT: { cmpnt<Sprite>()->setFacing(false); break; }
        case DIR_RIGHT: { cmpnt<Sprite>()->setFacing(true); break; }
        default: break;
    }
    cmpnt<RigidBody>()->setDirection(dir);
}
void GameObject::stop(const int dir)
{
    cmpnt<RigidBody>()->stopDirection(dir);
}
void GameObject::increase(const int cf)
{
    cmpnt<RigidBody>()->increase(cf);
}
void GameObject::decrease(const int cf)
{
    cmpnt<RigidBody>()->decrease(cf);
}
void GameObject::update(const float dt)
{
    for (auto [cmpnt_t, cmpnt] : cmpts) {
        cmpnt->update(dt);
    }
    if (cmpnt<RigidBody>()->isGrounded()) {
        if (cmpnt<RigidBody>()->isMoving()) {
            cmpnt<Animator>()->setState(AnimationState::moving);
        } else {
            cmpnt<Animator>()->setState(AnimationState::idle);
        }
    } else {
        cmpnt<Animator>()->setState(AnimationState::jumping);
    }
}
void GameObject::lateUpdate()
{

}
void GameObject::render(sf::RenderWindow &window)
{
    for (auto [cmpnt_t, cmpnt] : cmpts) {
        cmpnt->render(window);
    }
}
void GameObject::onColliding(const COLLIDER::group grp, const sf::Vector2f offset)
{
    if (abs(offset.x) < abs(offset.y)) {
        cmpnt<RigidBody>()->collidingXAxis(offset.x);
    }
    else {
        cmpnt<RigidBody>()->collidingYAxis(offset.y);
        if (offset.y < 0.0 && !cmpnt<RigidBody>()->isGrounded()) {
            cmpnt<RigidBody>()->setGrounded(true);
        }
    }
}
const GameObjectAsset& GameObject::getAsset() const
{
    return this->ast;
}
const sf::Vector2f GameObject::getPosition() const
{
    return cmpnt<RigidBody>()->getPosition();
}
const sf::Vector2i GameObject::getSize() const
{
    return cmpnt<RigidBody>()->getSize();
}
const sf::FloatRect GameObject::getRect() const
{
    return cmpnt<RigidBody>()->getRect();
}
const COLLIDER::group GameObject::getColliderGroup() const
{
    return this->col_group;
}

/**************************************************************************************************/

Boundary::Boundary(const sf::IntRect rect):
col_group(COLLIDER::group::floor), shape(sf::Vector2f(rect.width, rect.height)), rect(rect)
{
    shape.setPosition(rect.left, rect.top);
}
Boundary::Boundary(const sf::IntRect rect, const sf::Color c):
Boundary(rect)
{
    shape.setFillColor(color);
}
void Boundary::render(sf::RenderWindow &window)
{
    window.draw(shape);
}
const sf::Vector2f Boundary::getPosition() const
{
    return sf::Vector2f(rect.left, rect.top);
}
const sf::Vector2f Boundary::getSize() const
{
    return sf::Vector2f(rect.width, rect.height);
}
const sf::FloatRect Boundary::getRect() const
{
    return (sf::FloatRect) rect;
}
const COLLIDER::group Boundary::getColliderGroup() const
{
    return this->col_group;
}
