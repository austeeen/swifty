#ifndef ANIMATOR_HPP
#define ANIMATOR_HPP

#include "common.hpp"
#include "typedef.hpp"
#include "sys_physics_2d.hpp"

class GameObject;

/**************************************************************************************************/

class Component
{
public:
    Component(GameObject* obj);
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

    void setTextureRect(const sf::IntRect texture_rect);
    void setFacing(bool facing_right);

private:
    sf::Texture img_texture;
    sf::IntRect cur_rect;
    bool facing_right;
    sf::Sprite sprite;
};

/**************************************************************************************************/

enum class AnimationState { idle, moving, jumping };
enum class RollState { none, next, done };

struct Frame
{
    Frame(const float dur, const int row, const int indx, sf::Vector2i size);
    const float duration;
    const sf::IntRect texture_rect;
};

class Roll
{
public:
    Roll();
    Roll(animconfig roll_cfg, sf::Vector2i size);
    void reset();
    RollState nextFrame(const float dt);
    void triggerEarlyExit();
    const sf::IntRect getFrameRect() const;

private:
    animconfig cfg;
    int frame_indx;
    float frame_time;
    std::vector<Frame> frames;
};

class Animator: public Component
{
public:
    Animator(GameObject* obj);
    void setUp() override;
    void update(const float dt) override;

    void addAnimation(AnimationState state, std::shared_ptr<Roll> roll);
    void setState(AnimationState s);
    void endEarly();
    const AnimationState& getState() const;
    const sf::IntRect getFrameRect() const;

private:
    std::shared_ptr<Sprite> spr;
    std::map<AnimationState, std::shared_ptr<Roll>> animations;
    AnimationState cur, prev;
};

/**************************************************************************************************/

struct forces {
    float up, down, left, right, friction;
};

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
    const sf::Vector2f getPosition() const;
    const sf::Vector2i getSize() const;
    const sf::FloatRect getRect() const;
    void increase(const int cf);
    void decrease(const int cf);

protected:
    friend class Physics2DSystem;
    float f_grav, f_fric, f_jump, f_move;
    sf::Vector2f vel, acl;
    bool wants_to_jump, jumped_this_frame, grounded;
    int max_x_vel, moving_left, moving_right;

private:
    void updateForces();

    sf::FloatRect position_rect, collision_rect;
    int mass, speed, jump_power;
    float acl_gravity, friction;
    // forces frc;
};

#endif // ANIMATOR_HPP
