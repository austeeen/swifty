#ifndef CMP_RIGID_BODY_HPP
#define CMP_RIGID_BODY_HPP

#include "c_base.hpp"
#include <cmath>

class Body2D {
public:
    Body2D(GameObject* ast);
    void render(sf::RenderWindow &window);
    const sf::Vector2f getPosition() const;
    const sf::Vector2i getSize() const;
    const std::vector<CollisionRect>& getRects() const;

protected:
    friend class RigidBody;
    void setColliders(const std::vector<CollisionRect>& rects);
    void move(const float x, const float y);
    void updateColliders();

    void xCollision(const float offset);
    void yCollision(const float offset);

    void setFacing(bool facing);
    void reverseXaxis();
    void resetXaxis();

private:
    sf::RectangleShape createShape(sf::Color c);

    bool facing_right;
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
    void setDirection(const int dir);
    void stopDirection(const int dir);
    void jump();
    void setGrounded(bool is_grounded);
    void updatePosition(const float x, const float y);
    void collidingXAxis(const float x_offset);
    void collidingYAxis(const float y_offset);
    bool isGrounded() const;
    bool isMoving() const;
    bool jumpedThisFrame() const;
    void setCollisionRects(const std::vector<CollisionRect>& rects);
    void setFacing(bool facing);

    void increase(const BodyPhysics cf);
    void decrease(const BodyPhysics cf);
    void toggleDisplayBody();

    const sf::Vector2f getPosition() const;
    const sf::Vector2i getSize() const;
    const std::vector<CollisionRect>& getRects() const;

private:
    void updateForces();

    const float close_to_zero = 0.1;
    float f_grav, f_damp, f_jump, f_move;
    sf::Vector2f vel, acl;
    bool wants_to_jump, jumped_this_frame, grounded;
    int max_x_vel, moving_left, moving_right;
    bool display_body;
    std::shared_ptr<Body2D> body;
    int mass, speed, jump_power;
    float acl_gravity, damping;
};

#endif // CMP_RIGID_BODY_HPP
