#ifndef CMP_PHYSICS_2D_HPP
#define CMP_PHYSICS_2D_HPP

#include "component_base.hpp"

class RigidBody;

class Physics2D: public Component
{
    struct Force2D {
        float grav, move, damp, jump;
        void update(const PhysicsCoeffs& new_u);
    };
public:
    Physics2D(GameObject* obj);
    void build() override;
    void update(const float dt);

    void setMoving(const Dir4);
    void stopMoving(const Dir4);
    void jump();
    void terminateJump();

    void setState(ObjectState state);
    const ObjectState nextState();
    void onColliding(const sf::Vector2f& offset, const ColliderType colliding_type, const ColliderType type);
    void updateInertia(const sf::Vector2f& in);

    const sf::Vector2f& getVelocity() const;

    void increase(const PhysicsCoeffs::AsEnum cf);
    void decrease(const PhysicsCoeffs::AsEnum cf);

    void print() const;

private:
    ObjectState cur_state, next_state;
    std::shared_ptr<RigidBody> body;
    PhysicsCoeffs u;
    Force2D frc;
    int moving_left, moving_right, moving_dir, is_jumping;
    sf::Vector2f vel, inertia, acl, body_offset, other_offset;
    float falling_dt, block_falling;
};

#endif // CMP_PHYSICS_2D_HPP
