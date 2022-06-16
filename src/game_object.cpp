#include "game_object.hpp"

GameObject::GameObject(const GameObjectAsset ast):
col_group(CollisionGroup::object), ast(ast)
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
void GameObject::setUp()
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
void GameObject::update(const float dt)
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
void GameObject::lateUpdate()
{

}
void GameObject::render(sf::RenderWindow &window)
{
    for (auto [cmpnt_t, cmpnt] : cmpts) {
        cmpnt->render(window);
    }
}
void GameObject::move(const Dir4 dir)
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
void GameObject::stop(const Dir4 dir)
{
    cmpnt<RigidBody>()->stopDirection(dir);
}
void GameObject::jump()
{
    cmpnt<RigidBody>()->jump();
}
void GameObject::terminateJump()
{
    cmpnt<RigidBody>()->terminateJump();
    /*
    if(cmpnt<RigidBody>()->terminateJump()) {
        cmpnt<Animator>()->endEarly();
    }
    */
}
void GameObject::increase(const BodyPhysics cf)
{
    cmpnt<RigidBody>()->increase(cf);
}
void GameObject::decrease(const BodyPhysics cf)
{
    cmpnt<RigidBody>()->decrease(cf);
}
void GameObject::toggleRects()
{
    cmpnt<RigidBody>()->toggleDisplayBody();
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
const std::vector<CollisionRect>& GameObject::getRects() const
{
    return cmpnt<RigidBody>()->getRects();
}
const CollisionGroup GameObject::getColliderGroup() const
{
    return this->col_group;
}

/**************************************************************************************************/

Boundary::Boundary(const sf::IntRect rect):
    col_group(CollisionGroup::floor),
    rect(rect),
    shape(sf::Vector2f(rect.width, rect.height))
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
const CollisionGroup Boundary::getColliderGroup() const
{
    return this->col_group;
}
