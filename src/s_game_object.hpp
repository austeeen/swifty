#ifndef STATES_GAME_OBJECT_HPP
#define STATES_GAME_OBJECT_HPP

#include "common.hpp"

class GameObject;

class StateBase
{
public:
    StateBase(GameObject* obj): obj(obj) {};
    virtual void enter() {};
    virtual void exit() {};
    virtual ObjectState next() = 0;
    virtual void update(const float dt) {};
    virtual void lateUpdate() {};

protected:
    GameObject* obj;
    ObjectState previous;
};

class IdleState : public StateBase
{
public:
    IdleState(GameObject* obj);
    void enter() override;
    void exit() override;
    ObjectState next() override;
    void update(const float dt) override;
    void lateUpdate() override;
};

class RunningState : public StateBase
{
public:
    RunningState(GameObject* obj);
    void enter() override;
    void exit() override;
    ObjectState next() override;
    void update(const float dt) override;
    void lateUpdate() override;
};

class JumpingState : public StateBase
{
public:
    JumpingState(GameObject* obj);
    void enter() override;
    void exit() override;
    ObjectState next() override;
    void update(const float dt) override;
    void lateUpdate() override;
};

class FallingState : public StateBase
{
public:
    FallingState(GameObject* obj);
    void enter() override;
    void exit() override;
    ObjectState next() override;
    void update(const float dt) override;
    void lateUpdate() override;
};
#endif // STATES_GAME_OBJECT_HPP
