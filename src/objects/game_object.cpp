#include "game_object.hpp"

GameObject::GameObject(const GameObjectAsset ast):
    cur_state(ObjectState::idle), ast(ast), orientation(ast.facing_right ? Dir4::right : Dir4::left)
{
    cmpts[typeid(Sprite)] = std::make_shared<Sprite>(this);
    cmpts[typeid(Physics2D)] = std::make_shared<Physics2D>(this);
    cmpts[typeid(RigidBody)] = std::make_shared<RigidBody>(this);
    cmpts[typeid(Animator)] = std::make_shared<Animator>(this);

    // if (orientation == Dir4::right) {
    //     out::debug("GameObject()", "%s facing right", ast.name.c_str());
    // } else if (orientation == Dir4::left) {
    //     out::debug("GameObject()", "%s facing left", ast.name.c_str());
    // } else {
    //     out::debug("GameObject()", " %s unknown facing %d", ast.name.c_str(), (int) orientation);
    // }
}
void GameObject::build()
{
    for (auto [cmpnt_t, cmpnt] : cmpts) {
        cmpnt->build();
    }
}
void GameObject::setUp()
{
    setState(cur_state);
    for (auto [cmpnt_t, cmpnt] : cmpts) {
        cmpnt->setUp();
    }
}
void GameObject::update(const float dt)
{
    for (auto [cmpnt_t, cmpnt] : cmpts) {
        cmpnt->update(dt);
    }
}
void GameObject::lateUpdate()
{
    ObjectState next_state = this->cmpnt<Physics2D>()->nextState();
    if (cur_state != next_state) {
        setState(next_state);
    }
}
void GameObject::render(sf::RenderWindow &window)
{
    for (auto [cmpnt_t, cmpnt] : cmpts) {
        cmpnt->render(window);
    }
}
void GameObject::move(const Dir4 d)
{
    switch(d) {
        case Dir4::left: {
            cmpnt<Physics2D>()->setMoving(d);
            cmpnt<Sprite>()->flipTexture(d != orientation);
            cmpnt<RigidBody>()->updateFacing(d);
            break;
        }
        case Dir4::right: {
            cmpnt<Physics2D>()->setMoving(d);
            cmpnt<Sprite>()->flipTexture(d != orientation);
            cmpnt<RigidBody>()->updateFacing(d);
            break;
        }
        default: break;
    }
}
void GameObject::stop(const Dir4 d)
{
    cmpnt<Physics2D>()->stopMoving(d);
}
void GameObject::stopAll()
{
    cmpnt<Physics2D>()->stopMoving(Dir4::left);
    cmpnt<Physics2D>()->stopMoving(Dir4::right);
}
void GameObject::resetPosition()
{
    setStartPosition(this->start_pos);
}
void GameObject::setState(const ObjectState next_state)
{
    if (cur_state != next_state) {
        this->cur_state = next_state;
        this->cmpnt<Animator>()->setState(cur_state);
        this->cmpnt<Physics2D>()->setState(cur_state);
    }
}
void GameObject::setStartPosition(const sf::Vector2i pos)
{
    start_pos = pos;
    cmpnt<RigidBody>()->setPosition(pos.x, pos.y);    
}
void GameObject::toggleRects(const int opt)
{
    cmpnt<RigidBody>()->toggleDisplay(opt);
}
void GameObject::onColliding(const sf::Vector2f& offset, const ColliderType m_type, const ColliderType b_type) const
{
    this->cmpnt<Physics2D>()->onColliding(offset, m_type, b_type);
}
void GameObject::updateInertia(const sf::Vector2f& inertia) const
{
    this->cmpnt<Physics2D>()->updateInertia(inertia);
}
const GameObjectAsset& GameObject::getAsset() const
{
    return ast;
}
const Dir4 GameObject::getOrientation() const
{
    return orientation;
}
const sf::FloatRect& GameObject::getPositionRect() const
{
    return this->cmpnt<RigidBody>()->getPositionRect();
}
const std::string& GameObject::getName() const
{
    return ast.name;
}
const std::vector<CollisionRect>& GameObject::getColliders() const
{
    return this->cmpnt<RigidBody>()->getColliders();
}
const sf::Vector2f& GameObject::getVelocity() const
{
    return this->cmpnt<Physics2D>()->getVelocity();
}
