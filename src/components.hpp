#ifndef ANIMATOR_HPP
#define ANIMATOR_HPP

#include "common.hpp"
#include "typedef.hpp"
#include "sys_physics_2d.hpp"
#include "rsrc_tiled.hpp"

class GameObject;

/**************************************************************************************************/

class Component
{
public:
    Component(GameObject* obj);
    ~Component() { obj = nullptr; }
    virtual void setUp();
    virtual void update(const float dt);
    virtual void render(sf::RenderWindow &window);

public:
    GameObject* obj;
};

/**************************************************************************************************/

class Sprite: public Component
{
public:
    Sprite(GameObject* obj);
    void setUp() override;
    void update(const float dt) override;
    void render(sf::RenderWindow &window) override;

    void setTextureRect(const sf::IntRect& texture_rect);
    void setFacing(bool facing_right);

private:
    sf::Texture img_texture;
    sf::IntRect cur_rect;
    bool facing_right;
    sf::Sprite sprite;
    std::shared_ptr<RigidBody> body;
};

/**************************************************************************************************/

enum class RollState { none, next, done };

class Roll
{
public:
    Roll(std::shared_ptr<AnimRoll> roll);
    void reset();
    RollState nextFrame(const float dt);
    void triggerEarlyExit();
    const sf::IntRect getFrameRect() const;
    const std::vector<sf::FloatRect>& getCollisionRects() const;

private:
    int frame_indx, num_frames;
    float frame_time;
    bool one_shot, hold_last_frame;
    int end_early_frame;
    std::vector<std::shared_ptr<TileFrame>> frames;
};

class Animator: public Component
{
public:
    Animator(GameObject* obj);
    void setUp() override;
    void update(const float dt) override;
    void setState(AnimationState s);
    void endEarly();
    const AnimationState& getState() const;
    const sf::IntRect getFrameRect() const;

private:
    std::shared_ptr<Sprite> spr;
    std::shared_ptr<RigidBody> body;
    std::map<AnimationState, Roll*> animations;
    AnimationState cur, prev;
};

/**************************************************************************************************/

class RigidBody: public Component
{
public:
    RigidBody(GameObject* obj);
    void setUp() override;
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
    void setCollisionRects(const std::vector<sf::FloatRect>& rects);
    void updateFacing(bool facing_right);
    const sf::Vector2f getPosition() const;
    const sf::Vector2i getSize() const;
    const std::vector<sf::FloatRect>& getRects() const;
    void increase(const BodyPhysics cf);
    void decrease(const BodyPhysics cf);

protected:
    friend class Physics2DSystem;
    float f_grav, f_damp, f_jump, f_move;
    sf::Vector2f vel, acl;
    bool wants_to_jump, jumped_this_frame, grounded;
    int max_x_vel, moving_left, moving_right;

private:
    void updateForces();

    sf::FloatRect position_rect;
    std::vector<sf::FloatRect> collision_rects;
    int mass, speed, jump_power;
    float acl_gravity, damping;
};

#endif // ANIMATOR_HPP
