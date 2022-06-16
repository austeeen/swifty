#include "c_animator.hpp"
#include "c_sprite.hpp"
#include "c_rigid_body.hpp"
#include "game_object.hpp"

Roll::Roll(std::shared_ptr<AnimRoll> roll):
    frame_indx(0),
    frame_time(0.0f),
    one_shot(roll->one_shot),
    hold_last_frame(roll->hold_last_frame),
    end_early_frame(roll->end_early_frame),
    frames(roll->frames)
{
    num_frames = roll->frames.size();
}
void Roll::reset()
{
    frame_indx = 0;
    frame_time = 0.f;
}
RollState Roll::nextFrame(const float dt)
{
    RollState ret_state = RollState::none;

    frame_time += dt;
    if (frames[frame_indx]->duration < frame_time) {
        frame_indx ++;
        frame_time = 0.0f;
        ret_state = RollState::next;
    }
    else {
        return ret_state;
    }

    if (frame_indx == num_frames) {
        if (one_shot) {
            ret_state = RollState::done;
        }
        if (hold_last_frame) {
            if (ret_state == RollState::next) {
                ret_state = RollState::none;
            }
            frame_indx --;
        } else {
            frame_indx = 0;
        }
    }
    return ret_state;
}
void Roll::triggerEarlyExit()
{
    if (frame_indx < end_early_frame) {
        frame_indx = end_early_frame;
        frame_time = 0.0f;
    }
}
const sf::IntRect Roll::getFrameRect() const
{
    return frames[frame_indx]->texture_rect;
}
const std::vector<CollisionRect>& Roll::getCollisionRects() const
{
    return frames.at(frame_indx)->collision_rects;
}

Animator::Animator(GameObject* obj):
    Component(obj),
    spr(nullptr),
    cur(AnimationState::idle),
    prev(AnimationState::idle)
{}
void Animator::build()
{
    spr = obj->cmpnt<Sprite>();
    body = obj->cmpnt<RigidBody>();
    GameObjectAsset ast = obj->getAsset();
    for (auto& [id, roll] : ast.animation_rolls) {
        animations[id] = new Roll(roll);
    }
}
void Animator::setUp()
{
    spr->setTextureRect(animations[cur]->getFrameRect());
    body->setCollisionRects(animations[cur]->getCollisionRects());
}
void Animator::update(const float dt)
{
    switch(animations[cur]->nextFrame(dt))
    {
        case RollState::none: break;
        case RollState::next: {
            spr->setTextureRect(animations[cur]->getFrameRect());
            body->setCollisionRects(animations[cur]->getCollisionRects());
            break;
        }
        case RollState::done: {
            setPrevState();
            break;
        }
        default:
            break;
    }
}
void Animator::setState(AnimationState next_state)
{
    if (cur == next_state) {
        return;
    }

    if (animations.count(next_state) > 0) {
        animations[next_state]->reset();
        animations[cur]->reset();
        prev = cur;
        cur = next_state;
        spr->setTextureRect(animations[cur]->getFrameRect());
        body->setCollisionRects(animations[cur]->getCollisionRects());
    }
}
void Animator::setPrevState()
{
    if (cur == prev) {
        return;
    }

    if (animations.count(prev) > 0) {
        animations[prev]->reset();
        animations[cur]->reset();
        cur = prev;
        spr->setTextureRect(animations[cur]->getFrameRect());
        body->setCollisionRects(animations[cur]->getCollisionRects());
    }
}
void Animator::endEarly()
{
    animations[cur]->triggerEarlyExit();
}
const AnimationState& Animator::getState() const
{
    return cur;
}
const sf::IntRect Animator::getFrameRect() const
{
    return animations.at(cur)->getFrameRect();
}
