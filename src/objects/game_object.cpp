#include "game_object.hpp"

KinematicObject::KinematicObject(const GameObjectAsset ast):
    cur_state(ObjectState::idle), ast(ast)
{
    cmpts[typeid(Sprite)] = std::make_shared<Sprite>(this);
    cmpts[typeid(Physics2D)] = std::make_shared<Physics2D>(this);
    cmpts[typeid(RigidBody)] = std::make_shared<RigidBody>(this);
    cmpts[typeid(Animator)] = std::make_shared<Animator>(this);
}
void KinematicObject::setStartPosition(const int x, const int y)
{
    cmpnt<RigidBody>()->move(ast.start_pos.x, ast.start_pos.y);
}
const GameObjectAsset& KinematicObject::getAsset() const
{
    return ast;
}
void KinematicObject::toggleRects()
{
    cmpnt<RigidBody>()->toggleDisplay();
}
const std::string& KinematicObject::getName() const
{
    return ast.name;
}
