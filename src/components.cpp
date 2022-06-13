#include "components.hpp"
#include "game_object.hpp"

/**************************************************************************************************/

Component::Component(GameObject* obj): obj(obj)
{}
void Component::setUp()
{}
void Component::update(const float dt)
{}
void Component::render(sf::RenderWindow &window)
{}

/**************************************************************************************************/

Sprite::Sprite(GameObject* obj):
Component(obj), cur_rect(0, 0, 0, 0), facing_right(true)
{}
void Sprite::setUp()
{
    img_texture.loadFromFile(obj->getAsset().img_fp);
    cur_rect = obj->getAsset().start_texture_rect;
    sprite.setTexture(img_texture);
    sprite.setTextureRect(cur_rect);
}
void Sprite::setTextureRect(sf::IntRect texture_rect)
{
    cur_rect = texture_rect;
    if (!facing_right) {
        cur_rect.left += cur_rect.width;
        cur_rect.width = -cur_rect.width;
    }
    sprite.setTextureRect(cur_rect);
}
void Sprite::setFacing(bool facing)
{
    facing_right = facing;
}
void Sprite::update(const float dt)
{}
void Sprite::render(sf::RenderWindow &window)
{
    sprite.setPosition(this->obj->getPosition());
    window.draw(sprite);
}

/**************************************************************************************************/

Frame::Frame(const float dur, const int row, const int indx, sf::Vector2i size):
duration(dur), texture_rect(indx * size.x, row * size.y, size.x, size.y)
{}

Roll::Roll()
{}
Roll::Roll(animconfig cfg, sf::Vector2i size): cfg(cfg), frame_indx(0), frame_time(0.0f)
{
    if (cfg.frames.size() == 0) {
        for (int i = 0; i < cfg.num_frames; ++i) {
            frames.push_back(Frame(cfg.dur, cfg.row, i, size));
        }
    } else {
        for (int i : cfg.frames) {
            frames.push_back(Frame(cfg.dur, cfg.row, i, size));
        }
    }
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
    if (frames[frame_indx].duration < frame_time) {
        frame_indx ++;
        frame_time = 0.0f;
        ret_state = RollState::next;
    }

    if (frame_indx == cfg.num_frames) {
        if (cfg.one_shot) {
            ret_state = RollState::done;
        }
        if (cfg.hold_last_frame) {
            ret_state = RollState::none;
            frame_indx --;
        } else {
            frame_indx = 0;
        }
    }
    return ret_state;
}
void Roll::triggerEarlyExit()
{
    if (frame_indx < cfg.end_early_frame) {
        frame_indx = cfg.end_early_frame;
        frame_time = 0.0f;
    }
}
const sf::IntRect Roll::getFrameRect() const
{
    return frames[frame_indx].texture_rect;
}

Animator::Animator(GameObject* obj):
Component(obj),
spr(nullptr),
cur(AnimationState::idle),
prev(AnimationState::idle)
{}
void Animator::setUp()
{
    spr = obj->cmpnt<Sprite>();
    GameObjectAsset ast = obj->getAsset();
    animations[AnimationState::idle] = std::make_shared<Roll>(ast.idle_cfg, ast.size);
    animations[AnimationState::moving] = std::make_shared<Roll>(ast.moving_cfg, ast.size);
    animations[AnimationState::jumping] = std::make_shared<Roll>(ast.jumping_cfg, ast.size);
}
void Animator::update(const float dt)
{
    switch(animations[cur]->nextFrame(dt))
    {
        case RollState::none: break;
        case RollState::next: {
            spr->setTextureRect(animations[cur]->getFrameRect());
            break;
        }
        case RollState::done: {
            setState(prev);
            break;
        }
        default:
            break;
    }
}
void Animator::setState(AnimationState next_state)
{
    if (cur == next_state)
        return;

    auto anim = animations[next_state];
    if (anim) {
        anim->reset();
        animations[cur]->reset();
        prev = cur;
        cur = next_state;
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

/**************************************************************************************************/

RigidBody::RigidBody(GameObject* obj):
Component(obj), f_grav(0.0f), f_damp(0.0f), f_jump(0.0f), f_move(0.0f),
wants_to_jump(false), jumped_this_frame(false), grounded(false),
max_x_vel(0), moving_left(0), moving_right(0)
{}
void RigidBody::setUp()
{
    GameObjectAsset ast = obj->getAsset();
    position_rect = ast.rect;
    collision_rect = ast.collision_rect;
    collision_rect.left += position_rect.left;
    collision_rect.top += position_rect.top;

    mass = ast.mass;
    speed = ast.speed;
    max_x_vel = ast.max_x_vel;
    jump_power = ast.jump_power;
    acl_gravity = ast.acl_gravity;
    damping = ast.damping;
    wants_to_jump = false;
    jumped_this_frame = false;
    grounded = true;
    updateForces();

}
void RigidBody::render(sf::RenderWindow &window)
{
    sf::RectangleShape r;
    r.setOutlineThickness(1);
    r.setFillColor(sf::Color::Transparent);

    r.setOutlineColor(sf::Color::Green);
    r.setPosition(position_rect.left, position_rect.top);
    r.setSize(sf::Vector2f(position_rect.width, position_rect.height));
    window.draw(r);

    r.setOutlineColor(sf::Color::Cyan);
    r.setPosition(collision_rect.left, collision_rect.top);
    r.setSize(sf::Vector2f(collision_rect.width, collision_rect.height));
    window.draw(r);
}
void RigidBody::setDirection(const int dir)
{
    switch (dir) {
        case DIR_LEFT: { moving_left = 1; break; }
        case DIR_RIGHT: { moving_right = 1; break; }
    }
}
void RigidBody::stopDirection(const int dir)
{
    switch (dir) {
        case DIR_LEFT: { moving_left = 0; break; }
        case DIR_RIGHT: { moving_right = 0; break; }
    }
}
void RigidBody::jump()
{
    wants_to_jump = true;
}
void RigidBody::setGrounded(bool is_grounded)
{
    grounded = is_grounded;
}
void RigidBody::updatePosition(const float x, const float y)
{
    position_rect.left += x;
    position_rect.top += y;
    collision_rect.left += x;
    collision_rect.top += y;
}
void RigidBody::collidingXAxis(const float x_offset)
{
    position_rect.left += x_offset;
    collision_rect.left += x_offset;
    // vel.x = 0;
    if (vel.y < 0) {
        vel.y = ((int) vel.y) + 1;
    }
}
void RigidBody::collidingYAxis(const float y_offset)
{
    position_rect.top += y_offset;
    collision_rect.top += y_offset;

    // only kill y velocity if the collision is opposing the current velocity so we don't cancel
    // initial jump velocity
    // could also try to use 'jumped_this_frame' as a marker for when to kill velocity in this direction
    if (y_offset > 0 && vel.y < 0) {
        vel.y = 0;
    } else if (y_offset < 0 && vel.y > 0) {
        vel.y = 0;
    }
}
bool RigidBody::isGrounded() const
{
    return grounded;
}
bool RigidBody::isMoving() const
{
    return moving_right - moving_left;
}
const sf::Vector2f RigidBody::getPosition() const
{
    return sf::Vector2f(position_rect.left, position_rect.top);
}
const sf::Vector2i RigidBody::getSize() const
{
    return sf::Vector2i(position_rect.width, position_rect.height);
}
const sf::FloatRect RigidBody::getRect() const
{
    return this->collision_rect;
}
void RigidBody::increase(const BodyPhysics cf)
{
    switch(cf) {
        case BodyPhysics::mass: { mass += 10; break; }
        case BodyPhysics::speed: { speed += 1; break; }
        case BodyPhysics::max_x_vel: { max_x_vel += 5; break; }
        case BodyPhysics::jump_power: { jump_power += 1; break; }
        case BodyPhysics::gravity: { acl_gravity += 1; break; }
        case BodyPhysics::damping: { damping += 1; break; }
    }
    updateForces();
}
void RigidBody::decrease(const BodyPhysics cf)
{
    switch(cf) {
        case BodyPhysics::mass: { mass -= 10; break; }
        case BodyPhysics::speed: { speed -= 1; break; }
        case BodyPhysics::max_x_vel: { max_x_vel -= 5; break; }
        case BodyPhysics::jump_power: { jump_power -= 1; break; }
        case BodyPhysics::gravity: { acl_gravity -= 1; break; }
        case BodyPhysics::damping: { damping -= 1; break; }
    }
    updateForces();
}
void RigidBody::updateForces()
{
    f_grav = acl_gravity * mass;
    f_damp = damping;
    f_jump = jump_power * 100 / mass;
    f_move = speed * mass * 100;
    printf("[RigidBody] mass: %d | speed: %d | max x vel %d | jump power %d | damping: %f |  gravity: %f\n",
            mass, speed, max_x_vel, jump_power, damping, acl_gravity);
}
/*
Physics::Physics(GameObject* obj): Component(obj)
{
    timer = 0.f;
    weight = 1;
    speed = 1;
    damping = 1.0f;
    force = 1.0f;
    terminal_vel = force;
    memset(vel, 0.f, sizeof(vel));
    memset(acl, 0.f, sizeof(acl));
    memset(sgn, 0, sizeof(sgn));
    states[BodyPhysics::stateID::grounded] = std::make_shared<GroundedState>(this);
    states[BodyPhysics::stateID::in_air] = std::make_shared<InAirState>(this);
    cur_state = BodyPhysics::stateID::grounded;
}
void Physics::setUp()
{
    weight = obj->getAsset().weight;
    speed = obj->getAsset().speed;
    damping = obj->getAsset().damping;
    calculateCoefficients();
}
void Physics::update(const float dt)
{
    states[cur_state]->applyAccelerations(dt);

    obj->move((vel[DIR_RIGHT] - vel[DIR_LEFT]) * dt,
              (vel[DIR_DOWN] - vel[DIR_UP]) * dt);

    timer += dt;
    if (timer > 0.5f) {
        printf("acl: (%f, %f, %f, %f) | vel: (%f, %f, %f, %f)\n",
            acl[DIR_RIGHT], acl[DIR_LEFT], acl[DIR_UP], acl[DIR_DOWN],
            vel[DIR_RIGHT], vel[DIR_LEFT], vel[DIR_UP], vel[DIR_DOWN]);
        timer = 0.f;
    }
}
bool Physics::jump()
{
    if (cur_state != BodyPhysics::stateID::in_air) {
        cur_state = BodyPhysics::stateID::in_air;
        states[cur_state]->enter();
        acl[DIR_UP] = force;
        return true;
    }
    return false;
}
bool Physics::terminateJump()
{
    if (cur_state == BodyPhysics::stateID::in_air) {
        if (vel[DIR_UP] > terminal_vel) {
            vel[DIR_UP] = terminal_vel;
            return true;
        }
    }
    return false;
}
bool Physics::isMoving() const
{
    return acl[DIR_LEFT] || acl[DIR_RIGHT];
}
bool Physics::isGrounded() const
{
    return cur_state == BodyPhysics::stateID::grounded;
}
void Physics::setGrounded()
{
    cur_state = BodyPhysics::stateID::grounded;
}
void Physics::move(const int dir)
{
    sgn[dir] = 1;
}
void Physics::stop(const int dir)
{
    sgn[dir] = 0;
}
void Physics::calculateCoefficients()
{
    force = (speed * 50) / weight;
    terminal_vel = force * 0.75;
    printf("weight: %d | speed: %d | damping: %f | force: %f | terminal_vel %f\n", weight, speed, damping, force, terminal_vel);
}
void Physics::increase(const int cf)
{
    switch(cf) {
        case BodyPhysics::weight: { weight += 2; break; }
        case BodyPhysics::speed: { speed += 5; break; }
        case BodyPhysics::damping: { damping += 0.1f; break; }
    }
    calculateCoefficients();
}
void Physics::decrease(const int cf)
{
    switch(cf) {
        case BodyPhysics::weight: { weight -= 2; break; }
        case BodyPhysics::speed: { speed -= 5; break; }
        case BodyPhysics::damping: { damping -= 0.1f; break; }
    }
    calculateCoefficients();
}

PhysicsState::PhysicsState(Physics* cmpnt):
cmpnt(cmpnt)
{}
PhysicsState::~PhysicsState()
{
    cmpnt = nullptr;
}

GroundedState::GroundedState(Physics* cmpnt):
PhysicsState(cmpnt)
{}
void GroundedState::applyAccelerations(const float dt)
{
    accelerate(DIR_LEFT, dt);
    accelerate(DIR_RIGHT, dt);

    cmpnt->vel[DIR_DOWN] += cmpnt->force * dt;
    cmpnt->vel[DIR_DOWN] = cmpnt->vel[DIR_DOWN] / (1 + 2 * dt);

}
void GroundedState::accelerate(const int dir, const float dt)
{
    if (cmpnt->acl[dir]) {
        cmpnt->vel[dir] += cmpnt->force * dt;
        cmpnt->vel[dir] = cmpnt->vel[dir] / (1 + cmpnt->damping * dt);
    }
    else {
        cmpnt->vel[dir] -= cmpnt->force * dt;
        if (cmpnt->vel[dir] < 0) {
            cmpnt->vel[dir] = 0;
        }
    }
}

InAirState::InAirState(Physics* cmpnt):
PhysicsState(cmpnt)
{}
void InAirState::enter()
{
    // in air, allow user to control x movement with only a portion of its regular ground force
    x_force = cmpnt->force / 2;

    // in air, player's x velocity is always capped by its x velocity magnitude when jump was triggered.
    max_x_vel = abs(cmpnt->vel[DIR_RIGHT] - cmpnt->vel[DIR_LEFT]);

    // in air, player's x velocity is under-damped.
    x_damping = 0.5f;
}
void InAirState::applyAccelerations(const float dt)
{
    accelerate(DIR_LEFT, dt);
    accelerate(DIR_RIGHT, dt);

    cmpnt->vel[DIR_DOWN] += cmpnt->force * dt;
    cmpnt->vel[DIR_DOWN] = cmpnt->vel[DIR_DOWN] / (1 + 2 * dt);

    if (cmpnt->vel[DIR_UP]) {
        cmpnt->vel[DIR_UP] -= cmpnt->force * dt;
        if(cmpnt->vel[DIR_UP] < 0) {
            cmpnt->vel[DIR_UP] = 0;
        }
    }
}
void InAirState::accelerate(const int dir, const float dt)
{
    // cap the user's x velocity to its initial jump x velocity
    if (cmpnt->vel[dir] > max_x_vel) {
        return;
    }
    // use a lower force value to allow player to control movement in air
    else if (cmpnt->acl[dir]) {
        cmpnt->vel[dir] += x_force * dt;
        cmpnt->vel[dir] = cmpnt->vel[dir] / (1 + x_damping * dt);
    }
}
*/
