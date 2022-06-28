#include "game_object.hpp"

GameObject::GameObject(const GameObjectAsset ast):
    cur_state(ObjectState::idle), ast(ast)
{
    cmpts[typeid(Sprite)] = std::make_shared<Sprite>(this);
    cmpts[typeid(Physics2D)] = std::make_shared<Physics2D>(this);
    cmpts[typeid(RigidBody)] = std::make_shared<RigidBody>(this);
    cmpts[typeid(Animator)] = std::make_shared<Animator>(this);
}
void GameObject::setStartPosition(const int x, const int y)
{
    cmpnt<RigidBody>()->move(x, y);
}
const GameObjectAsset& GameObject::getAsset() const
{
    return ast;
}
void GameObject::toggleRects()
{
    cmpnt<RigidBody>()->toggleDisplay();
}
const std::string& GameObject::getName() const
{
    return ast.name;
}
