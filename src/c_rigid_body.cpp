#include "c_rigid_body.hpp"
#include "game_object.hpp"

Body2D::Body2D(GameObject* obj): facing_right(true)
{
    GameObjectAsset ast = obj->getAsset();
    position_rect = ast.rect;
    pos_shape = createShape(sf::Color::Green);
}
void Body2D::render(sf::RenderWindow &window)
{
    pos_shape.setPosition(position_rect.left, position_rect.top);
    pos_shape.setSize(sf::Vector2f(position_rect.width, position_rect.height));
    window.draw(pos_shape);

    for (size_t i = 0; i < collision_shapes.size(); i ++) {
        collision_shapes[i].setPosition(collision_rects[i].rect.left, collision_rects[i].rect.top);
        collision_shapes[i].setSize(sf::Vector2f(collision_rects[i].rect.width, collision_rects[i].rect.height));
        window.draw(collision_shapes[i]);
    }
}
const sf::Vector2f Body2D::getPosition() const
{
    return sf::Vector2f(position_rect.left, position_rect.top);
}
const sf::Vector2i Body2D::getSize() const
{
    return sf::Vector2i(position_rect.width, position_rect.height);
}
const std::vector<CollisionRect>& Body2D::getRects() const
{
    return collision_rects;
}
void Body2D::setColliders(const std::vector<CollisionRect>& rects)
{
    collision_rects.clear();
    copy(rects.begin(), rects.end(), back_inserter(collision_rects));

    if (!facing_right) {
        reverseXaxis();
    }

    updateColliders();

    if(collision_rects.size() != collision_shapes.size()) {
        collision_shapes.clear();
        for (size_t i = 0; i < collision_rects.size(); i ++) {
            collision_shapes.push_back(createShape(sf::Color::Blue));
        }
    }
}
void Body2D::move(const float x, const float y)
{
    position_rect.left += x;
    position_rect.top += y;
    updateColliders();
}
void Body2D::updateColliders()
{
    for (auto& col_rect : collision_rects) {
        col_rect.rect.left = position_rect.left + col_rect.offset.x;
        col_rect.rect.top = position_rect.top + col_rect.offset.y;
    }
}
void Body2D::xCollision(const float offset)
{
    position_rect.left += offset;
    for (auto& col_rect : collision_rects) {
        col_rect.rect.left += offset;
    }
}
void Body2D::yCollision(const float offset)
{
    position_rect.top += offset;
    for (auto& col_rect : collision_rects) {
        col_rect.rect.top += offset;
    }
}
void Body2D::setFacing(bool facing)
{
    facing_right = facing;
    if (!facing_right) {
        reverseXaxis();
    } else {
        resetXaxis();
    }
}
void Body2D::reverseXaxis()
{
    for (auto& col_rect : collision_rects) {
        col_rect.offset.x = (position_rect.width - col_rect.offset.x) - col_rect.rect.width;
    }
}
void Body2D::resetXaxis()
{
    for (auto& col_rect : collision_rects) {
        col_rect.offset.x = position_rect.width - (col_rect.offset.x + col_rect.rect.width);
    }
}
sf::RectangleShape Body2D::createShape(sf::Color c)
{
    sf::RectangleShape shape;
    shape.setOutlineThickness(1);
    shape.setFillColor(sf::Color::Transparent);
    shape.setOutlineColor(c);
    return shape;
}

/**************************************************************************************************/

RigidBody::RigidBody(GameObject* obj):
    Component(obj),
    f_grav(0.0f),
    f_damp(0.0f),
    f_jump(0.0f),
    f_move(0.0f),
    wants_to_jump(false),
    jumped_this_frame(false),
    grounded(false),
    max_x_vel(0),
    moving_left(0),
    moving_right(0),
    display_body(false)
{}
void RigidBody::build()
{
    body = std::make_shared<Body2D>(obj);
    GameObjectAsset ast = obj->getAsset();
    mass = ast.mass;
    speed = ast.speed;
    max_x_vel = ast.max_x_vel;
    jump_power = ast.jump_power;
    acl_gravity = ast.acl_gravity;
    damping = ast.damping;
}
void RigidBody::setUp()
{
    updateForces();
}
void RigidBody::update(const float dt)
{
    // ACCELERATION
    acl.x = (moving_right - moving_left) * f_move;
    acl.y = f_grav;

    if (wants_to_jump) {
        wants_to_jump = false;
        if (grounded) {
            jumped_this_frame = true;
            setGrounded(false);
            vel.y -= f_jump;
        }
    } else {
        jumped_this_frame = false;
    }

    // VELOCITY
    vel.x += acl.x * dt;
    vel.y += acl.y * dt;

    if (vel.x != 0.f) {
        if (fabs(vel.x) > max_x_vel) {
            if (vel.x < 0) {
                vel.x = -max_x_vel;
            } else {
                vel.x = max_x_vel;
            }
        } else if (fabs(vel.x) < close_to_zero) {
            vel.x = 0.f;
        } else {
            // should ignore damping horizontally when in air
            vel.x = vel.x / (1 + f_damp * dt);
        }
    }

    updatePosition(vel.x * dt, vel.y * dt);
}

void RigidBody::render(sf::RenderWindow &window)
{
    if (display_body) {
        body->render(window);
    }
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
    printf("(RigidBody) wants to jump...\n");
}
void RigidBody::setGrounded(bool is_grounded)
{
    grounded = is_grounded;
}
void RigidBody::updatePosition(const float x, const float y)
{
    body->move(x, y);
}
void RigidBody::collidingXAxis(const float x_offset)
{
    body->xCollision(x_offset);
    // vel.x = 0;
    if (vel.y < 0) {
        vel.y = ((int) vel.y) + 1;
    }
}
void RigidBody::collidingYAxis(const float y_offset)
{
    body->yCollision(y_offset);
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
bool RigidBody::jumpedThisFrame() const
{
    return jumped_this_frame;
}
void RigidBody::setCollisionRects(const std::vector<CollisionRect>& rects)
{
    body->setColliders(rects);
}
void RigidBody::setFacing(bool facing)
{
    body->setFacing(facing);
}
const sf::Vector2f RigidBody::getPosition() const
{
    return body->getPosition();
}
const sf::Vector2i RigidBody::getSize() const
{
    return body->getSize();
}
const std::vector<CollisionRect>& RigidBody::getRects() const
{
    return body->getRects();
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
void RigidBody::toggleDisplayBody()
{
    display_body = !display_body;
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
