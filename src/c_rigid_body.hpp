#ifndef CMP_RIGID_BODY_HPP
#define CMP_RIGID_BODY_HPP

#include "c_base.hpp"
#include <cmath>

class Body2D {
public:
    Body2D(GameObject* ast);
    void setColliders(const std::vector<CollisionRect>& rects);
    void move(const float x, const float y);
    void updateFacing(const Dir4 next_facing);
    void xCollision(const float offset);
    void yCollision(const float offset);
    void render(sf::RenderWindow &window);

    const sf::Vector2f getPosition() const;
    const sf::Vector2i getSize() const;
    const std::vector<CollisionRect>& getRects() const;

private:
    void updateColliders();
    void faceLeft();
    void faceRight();
    sf::RectangleShape createShape(sf::Color c);

    Dir4 cur_facing;
    
    sf::FloatRect position_rect;
    std::vector<CollisionRect> collision_rects;
    sf::RectangleShape pos_shape;
    std::vector<sf::RectangleShape> collision_shapes;
};

class RigidBody: public Component
{
public:
    RigidBody(GameObject* obj);
    void build() override;
    void setUp() override;
    void update(const float dt);
    void render(sf::RenderWindow &window) override;

    void setState(ObjectState state);

    void setDirection(const Dir4);
    void stopDirection(const Dir4);
    void jump();
    void terminateJump();
    const ObjectState getState() const;
    void onColliding(const sf::Vector2f offset, ColliderType type);

    void setCollisionRects(const std::vector<CollisionRect>& rects);
    void setFacing(bool facing);

    void increase(const BodyPhysics cf);
    void decrease(const BodyPhysics cf);
    void toggleDisplayBody();

    const sf::Vector2f getPosition() const;
    const sf::Vector2f getVelocity() const;
    const sf::Vector2i getSize() const;
    const std::vector<CollisionRect>& getRects() const;

private:
    void updateForces();

    ObjectState cur_state;
    std::shared_ptr<Body2D> body;
    float f_grav, f_damp, f_jump, f_move, acl_gravity, damping;
    int max_x_vel, moving_left, moving_right, mass, speed, jump_power;
    bool display_body;
    sf::Vector2f vel, acl, collision_offset;
};

#endif // CMP_RIGID_BODY_HPP
