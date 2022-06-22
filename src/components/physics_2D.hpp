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
    Physics2D(Player* obj);
    void build() override;
    void update(const float dt);

    void setMoving(const Dir4);
    void stopMoving(const Dir4);
    void jump();
    void terminateJump();

    void setState(ObjectState state);
    const ObjectState nextState();
    void onColliding(const sf::Vector2f& offset, ColliderType type);

    const sf::Vector2f getVelocity() const;

    void increase(const PhysicsCoeffs::AsEnum cf);
    void decrease(const PhysicsCoeffs::AsEnum cf);

    void print() const;

private:
    ObjectState cur_state, next_state;
    std::shared_ptr<RigidBody> body;
    PhysicsCoeffs u;
    Force2D frc;
    int moving_left, moving_right, moving_dir, is_jumping;
    sf::Vector2f vel, acl, body_offset, other_offset;
    float falling_dt, block_falling;
};

#endif // CMP_PHYSICS_2D_HPP