#include "game_object.hpp"

GameObject::GameObject(const GameObjectAsset ast):
    cur_state(ObjectState::idle), ast(ast)
{
    cmpts[typeid(Sprite)] = std::make_shared<Sprite>(this);
    cmpts[typeid(Physics2D)] = std::make_shared<Physics2D>(this);
    cmpts[typeid(RigidBody)] = std::make_shared<RigidBody>(this);
    cmpts[typeid(Animator)] = std::make_shared<Animator>(this);
}
void GameObject::setUp()
{
    for (auto [cmpnt_t, cmpnt] : cmpts) {
        cmpnt->build();
    }
    setState(cur_state);
    for (auto [cmpnt_t, cmpnt] : cmpts) {
        cmpnt->setUp();
    }
}
void GameObject::update(const float dt)
{
    this->cmpnt<Animator>()->update(dt);
    this->cmpnt<Physics2D>()->update(dt);
}
void GameObject::lateUpdate()
{
    ObjectState next = this->cmpnt<Physics2D>()->nextState();
    if (next != cur_state) {
        cur_state = next;
        setState(cur_state);
    }
}
void GameObject::render(sf::RenderWindow &window)
{
    for (auto [cmpnt_t, cmpnt] : cmpts) {
        cmpnt->render(window);
    }
}
void GameObject::setState(const ObjectState s)
{
    this->cmpnt<Animator>()->setState(cur_state);
    this->cmpnt<Physics2D>()->setState(cur_state);
}
void GameObject::setStartPosition(const int x, const int y)
{
    cmpnt<RigidBody>()->move(x, y);
}
void GameObject::toggleRects()
{
    cmpnt<RigidBody>()->toggleDisplay();
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
