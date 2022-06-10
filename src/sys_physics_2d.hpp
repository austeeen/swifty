#ifndef PHYSICS_2D_HPP
#define PHYSICS_2D_HPP

#include "common.hpp"
#include "typedef.hpp"
#include <cmath>

class RigidBody;

class Physics2DSystem
{
public:
    void update(std::shared_ptr<RigidBody> obj, const float dt);

protected:
    void jump(std::shared_ptr<RigidBody> obj);
    void applyGravity(std::shared_ptr<RigidBody> obj, const float dt);
    void applyFriction(std::shared_ptr<RigidBody> obj, const float dt);
    void updateAccelerationX(std::shared_ptr<RigidBody> obj, const float dt);
    void updateAccelerationY(std::shared_ptr<RigidBody> obj, const float dt);
    void updatePosition(std::shared_ptr<RigidBody> obj, const float dt);

private:
    const float close_to_zero = 0.1;

    float slide_time = 0.0;
    bool still_moving = false;
};




#endif // PHYSICS_2D_HPP
