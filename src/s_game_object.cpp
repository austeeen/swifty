#include "s_game_object.hpp"
#include "game_object.hpp"

IdleState::IdleState(GameObject* obj):
    StateBase(obj)
{}
void IdleState::enter()
{
    obj->cmpnt<Animator>()->setState(ObjectState::idle);
    obj->cmpnt<RigidBody>()->setState(ObjectState::idle);
}
void IdleState::exit()
{}
ObjectState IdleState::next()
{
    return obj->cmpnt<RigidBody>()->getState();
}
void IdleState::update(const float dt)
{
    obj->cmpnt<Animator>()->update(dt);
    obj->cmpnt<RigidBody>()->update(dt);
}
void IdleState::lateUpdate()
{}

/**************************************************************************************************/

RunningState::RunningState(GameObject* obj):
    StateBase(obj)
{}
void RunningState::enter()
{
    obj->cmpnt<Animator>()->setState(ObjectState::running);
    obj->cmpnt<RigidBody>()->setState(ObjectState::running);
}
void RunningState::exit()
{}
ObjectState RunningState::next()
{
    return obj->cmpnt<RigidBody>()->getState();
}
void RunningState::update(const float dt)
{
    obj->cmpnt<Animator>()->update(dt);
    obj->cmpnt<RigidBody>()->update(dt);
}
void RunningState::lateUpdate()
{}

/**************************************************************************************************/

JumpingState::JumpingState(GameObject* obj):
    StateBase(obj)
{}
void JumpingState::enter()
{
    obj->cmpnt<Animator>()->setState(ObjectState::jumping);
    obj->cmpnt<RigidBody>()->setState(ObjectState::jumping);
}
void JumpingState::exit()
{}
ObjectState JumpingState::next()
{
    return obj->cmpnt<RigidBody>()->getState();
}
void JumpingState::update(const float dt)
{
    obj->cmpnt<Animator>()->update(dt);
    obj->cmpnt<RigidBody>()->update(dt);
}
void JumpingState::lateUpdate()
{}

/**************************************************************************************************/

FallingState::FallingState(GameObject* obj):
    StateBase(obj)
{}
void FallingState::enter()
{
    obj->cmpnt<Animator>()->setState(ObjectState::falling);
    obj->cmpnt<RigidBody>()->setState(ObjectState::falling);
}
void FallingState::exit()
{}
ObjectState FallingState::next()
{
    return obj->cmpnt<RigidBody>()->getState();
}
void FallingState::update(const float dt)
{
    obj->cmpnt<Animator>()->update(dt);
    obj->cmpnt<RigidBody>()->update(dt);
}
void FallingState::lateUpdate()
{}
