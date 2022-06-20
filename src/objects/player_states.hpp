#ifndef STATES_GAME_OBJECT_HPP
#define STATES_GAME_OBJECT_HPP

/*

#include "../common.hpp"

class Player;

class StateBase
{
public:
    StateBase(Player* obj): obj(obj) {};
    virtual void enter() {};
    virtual void exit() {};
    virtual ObjectState next() = 0;
    virtual void update(const float dt) {};
    virtual void lateUpdate() {};

protected:
    Player* obj;
    ObjectState previous;
};

class IdleState : public StateBase
{
public:
    IdleState(Player* obj);
    void enter() override;
    void exit() override;
    ObjectState next() override;
    void update(const float dt) override;
    void lateUpdate() override;
};

class RunningState : public StateBase
{
public:
    RunningState(Player* obj);
    void enter() override;
    void exit() override;
    ObjectState next() override;
    void update(const float dt) override;
    void lateUpdate() override;
};

class JumpingState : public StateBase
{
public:
    JumpingState(Player* obj);
    void enter() override;
    void exit() override;
    ObjectState next() override;
    void update(const float dt) override;
    void lateUpdate() override;
};

class FallingState : public StateBase
{
public:
    FallingState(Player* obj);
    void enter() override;
    void exit() override;
    ObjectState next() override;
    void update(const float dt) override;
    void lateUpdate() override;
};
*/

#endif // STATES_GAME_OBJECT_HPP
