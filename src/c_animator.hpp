#ifndef CMP_ANIMATOR_HPP
#define CMP_ANIMATOR_HPP

#include "c_base.hpp"

class Sprite;
class RigidBody;

enum class RollState { none, next, done };

class Roll
{
public:
    Roll(std::shared_ptr<AnimRoll> roll);
    void reset();
    RollState nextFrame(const float dt);
    void triggerEarlyExit();
    const sf::IntRect getFrameRect() const;
    const std::vector<CollisionRect>& getCollisionRects() const;

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
    void build() override;
    void setUp() override;
    void update(const float dt) override;
    void setState(AnimationState s);
    void setPrevState();
    void endEarly();
    const AnimationState& getState() const;
    const sf::IntRect getFrameRect() const;

private:
    std::shared_ptr<Sprite> spr;
    std::shared_ptr<RigidBody> body;
    std::map<AnimationState, Roll*> animations;
    AnimationState cur, prev;
};

#endif // CMP_ANIMATOR_HPP
