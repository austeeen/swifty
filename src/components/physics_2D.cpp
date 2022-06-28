#include "physics_2D.hpp"
#include "rigid_body.hpp"
#include "../objects/game_object.hpp"

Physics2D::Physics2D(KinematicObject* obj):
    Component(obj),
    cur_state(ObjectState::idle),
    next_state(ObjectState::idle),
    moving_left(0), moving_right(0), moving_dir(0), is_jumping(0),
    vel(0, 0), inertia(0, 0), acl(0, 0), body_offset(0, 0), other_offset(0, 0),
    falling_dt(0), block_falling(0.1)
{}
void Physics2D::build()
{
    body = obj->cmpnt<RigidBody>();
    GameObjectAsset ast = obj->getAsset();
    this->u = ast.coeffs;
    frc.update(u);
}
void Physics2D::update(const float dt)
{
    falling_dt += dt;
    // ACCELERATION
    acl.x = moving_dir * frc.move;
    acl.y = frc.grav;

    // VELOCITY
    vel.x += acl.x * dt;
    vel.y += acl.y * dt;

    if (is_jumping) {
        vel.y -= frc.jump * dt;
    }

    if (fabs(vel.x) < FLT_ZERO) {
        vel.x = 0.f;
    } else if (vel.x > u.maxvel) {
        vel.x = u.maxvel;
    } else if (vel.x < -u.maxvel) {
        vel.x = -u.maxvel;
    } else { // apply damping
        vel.x = vel.x / (1 + frc.damp * dt);
    }
    if (fabs(vel.y) < 0.1) {
        vel.y = 0.f;
    }

    // printf("Physics2D: v(%f, %f)\n", vel.x, vel.y);
    // POSITION
    body->move((vel.x + inertia.x) * dt, (vel.y + inertia.y) * dt);
}
void Physics2D::setMoving(const Dir4 dir)
{
    switch (dir) {
        case Dir4::left:  { moving_left  = 1; break; }
        case Dir4::right: { moving_right = 1; break; }
        default: { break; }
    }
    moving_dir = moving_right - moving_left;
}
void Physics2D::stopMoving(const Dir4 dir)
{
    switch (dir) {
        case Dir4::left: { moving_left = 0; break; }
        case Dir4::right: { moving_right = 0; break; }
        default: { break; }
    }
    moving_dir = moving_right - moving_left;
}
void Physics2D::jump()
{
    if (cur_state == ObjectState::idle || cur_state == ObjectState::running) {
        is_jumping = 1;
        vel.y = -frc.jump;
    }
}
void Physics2D::terminateJump()
{
    is_jumping = 0;
}
void Physics2D::setState(ObjectState state)
{
    cur_state = state;
}
const ObjectState Physics2D::nextState()
{
    ObjectState next_state = cur_state;
    switch (cur_state) {
        case ObjectState::jumping: {
            if (vel.y >= 0.f) {
                next_state = ObjectState::falling;
            }
            break;
        }
        case ObjectState::falling: {
            if (vel.y <= 0.f) {
                if (moving_dir) {
                    next_state = ObjectState::running;
                } else {
                    next_state = ObjectState::idle;
                }
            } else {
                next_state = ObjectState::falling;
            }
            // else if wall sliding
            break;
        }
        default: { // covers running or idle
            if (moving_dir) {
                next_state = ObjectState::running;
            } else {
                next_state = ObjectState::idle;
            }
            if (vel.y < 0.f) {
                next_state = ObjectState::jumping;
            } else if (vel.y > 1.5f && falling_dt > block_falling) {
                falling_dt = 0.0f;
                next_state = ObjectState::falling;
            }
            break;
        }
    }
    return next_state;
}
void Physics2D::onColliding(const sf::Vector2f& offset, const ColliderType colliding_type, const ColliderType type)
{
    if (fabs(offset.x) < fabs(offset.y)) {
        body->xCollision(offset.x);
        vel.x = 0.f;
        if (colliding_type == ColliderType::immovable) {
            inertia.x = 0;
        }
    } else {
        if (cur_state == ObjectState::jumping) {
            if (offset.y > 0.f) {
                vel.y = vel.y * 0.5f;
                body->yCollision(offset.y);
                // idea -- x velocity takes a hit for 'friction' ?
            } else {
                vel.y = 0.f;
                cur_state = ObjectState::falling;
            }
        } else {
            body->yCollision(offset.y);
            if (type == ColliderType::body) {
                vel.y = 0.f;
            }
        }
        if (colliding_type == ColliderType::immovable) {
            inertia.y = 0;
        }
    }
}
void Physics2D::updateInertia(const sf::Vector2f& in)
{
    inertia = in;
}
const sf::Vector2f Physics2D::getVelocity() const
{
    return vel;
}
void Physics2D::increase(const PhysicsCoeffs::AsEnum cf)
{
    u.increase(cf);
    frc.update(u);
}
void Physics2D::decrease(const PhysicsCoeffs::AsEnum cf)
{
    u.decrease(cf);
    frc.update(u);
}
void Physics2D::print() const
{
    printf("[Physics2D] %s %s acl(%f, %f) vel(%f, %f)\n", obj->getName().c_str(), out::toStr(cur_state).c_str(), acl.x, acl.y, vel.x, vel.y);
}
void Physics2D::Force2D::update(const PhysicsCoeffs& new_u)
{
    grav = new_u.gravity * new_u.mass;
    damp = new_u.damping;
    jump = new_u.jump * 100 / new_u.mass;
    move = new_u.speed * new_u.mass * 100;
    std::cout << new_u << std::endl;
}
