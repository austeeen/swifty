#include "animator.hpp"
#include "sprite.hpp"
#include "rigid_body.hpp"
#include "../objects/player.hpp"

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

/**************************************************************************************************/

Animator::Animator(Player* obj):
    Component(obj),
    spr(nullptr),
    cur(ObjectState::idle),
    prev(ObjectState::idle)
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
    updateObject();
}
void Animator::update(const float dt)
{
    switch(animations[cur]->nextFrame(dt))
    {
        case RollState::none: break;
        case RollState::next: {
            updateObject();
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
void Animator::setState(ObjectState next_state)
{
    if (cur == next_state) {
        return;
    }
    if (animations.count(next_state) > 0) {
        animations[next_state]->reset();
        animations[cur]->reset();
        prev = cur;
        cur = next_state;
        updateObject();
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
        updateObject();
    }
}
void Animator::endEarly()
{
    animations[cur]->triggerEarlyExit();
}
const ObjectState& Animator::getState() const
{
    return cur;
}
const sf::IntRect Animator::getFrameRect() const
{
    return animations.at(cur)->getFrameRect();
}
void Animator::updateObject()
{
    spr->setTextureRect(animations[cur]->getFrameRect());
    body->setColliders(animations[cur]->getCollisionRects());
}
