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

    void setState(ObjectState state);
    const ObjectState getState() const;

    void setMoving(const Dir4);
    void stopMoving(const Dir4);
    void jump();
    void terminateJump();
    void onColliding(const sf::Vector2f offset, ColliderType type);
    const sf::Vector2f getVelocity() const;

    void increase(const PhysicsCoeffs::AsEnum cf);
    void decrease(const PhysicsCoeffs::AsEnum cf);


private:
    ObjectState cur_state;
    std::shared_ptr<RigidBody> body;
    PhysicsCoeffs u;
    Force2D frc;
    int moving_left, moving_right;
    sf::Vector2f vel, acl;
};

#endif // CMP_PHYSICS_2D_HPP
