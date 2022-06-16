#include "c_rigid_body.hpp"
#include "game_object.hpp"

Body2D::Body2D(GameObject* obj):
    cur_facing(Dir4::right)
{
    GameObjectAsset ast = obj->getAsset();
    position_rect = ast.rect;
    pos_shape = createShape(sf::Color::Green);
}
void Body2D::setColliders(const std::vector<CollisionRect>& rects)
{
    collision_rects.clear();
    copy(rects.begin(), rects.end(), back_inserter(collision_rects));
    if (cur_facing == Dir4::left) {
        faceLeft();
    }
    updateColliders();
}
void Body2D::move(const float x, const float y)
{
    position_rect.left += x;
    position_rect.top += y;
    updateColliders();
}
void Body2D::updateFacing(const Dir4 next_facing)
{
    if (next_facing == cur_facing) {
        return;
    }
    cur_facing = next_facing;
    if (cur_facing == Dir4::left) {
        faceLeft();
    } else {
        faceRight();
    }
    updateColliders();
}
void Body2D::updateColliders()
{
    for (auto& col_rect : collision_rects) {
        col_rect.aabb.left = position_rect.left + col_rect.offset.x;
        col_rect.aabb.top = position_rect.top + col_rect.offset.y;
    }
}
void Body2D::faceLeft()
{
    for (auto& col_rect : collision_rects) {
        col_rect.offset.x = position_rect.width - col_rect.aabb.width - col_rect.offset.x;
    }
}
void Body2D::faceRight()
{
    for (auto& col_rect : collision_rects) {
        col_rect.offset.x = position_rect.width - (col_rect.offset.x + col_rect.aabb.width);
    }
}
void Body2D::xCollision(const float offset)
{
    position_rect.left += offset;
    for (auto& col_rect : collision_rects) {
        col_rect.aabb.left += offset;
    }
}
void Body2D::yCollision(const float offset)
{
    position_rect.top += offset;
    for (auto& col_rect : collision_rects) {
        col_rect.aabb.top += offset;
    }
}
void Body2D::render(sf::RenderWindow &window)
{
    pos_shape.setPosition(position_rect.left, position_rect.top);
    pos_shape.setSize(sf::Vector2f(position_rect.width, position_rect.height));
    window.draw(pos_shape);

    if (collision_rects.size() != collision_shapes.size()) {
        collision_shapes.clear();
        for (size_t i = 0; i < collision_rects.size(); i ++) {
            collision_shapes.push_back(createShape(sf::Color::Blue));
        }
    }

    for (size_t i = 0; i < collision_shapes.size(); i ++) {
        collision_shapes[i].setPosition(collision_rects[i].aabb.left, collision_rects[i].aabb.top);
        collision_shapes[i].setSize(sf::Vector2f(collision_rects[i].aabb.width, collision_rects[i].aabb.height));
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
    cur_state(ObjectState::idle),
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
    GameObjectAsset ast = obj->getAsset();
    body->move(ast.start_pos.x, ast.start_pos.y);
}
void RigidBody::update(const float dt)
{
    // ACCELERATION
    acl.x = (moving_right - moving_left) * f_move;
    acl.y = f_grav;

    // VELOCITY
    vel.x += acl.x * dt;
    vel.y += acl.y * dt;

    if (fabs(vel.x) < FLT_ZERO) {
        vel.x = 0.f;
    } else if (vel.x > max_x_vel) {
        vel.x = max_x_vel;
    } else if (vel.x < -max_x_vel) {
        vel.x = -max_x_vel;
    } else { // apply damping
        vel.x = vel.x / (1 + f_damp * dt);
    }
    if (fabs(vel.y) < 0.1) {
        vel.y = 0.f;
    }
    // POSITION
    body->move(vel.x * dt, vel.y * dt);
}
void RigidBody::render(sf::RenderWindow &window)
{
    if (display_body) {
        body->render(window);
    }
}
void RigidBody::setState(ObjectState state)
{
    cur_state = state;
}
void RigidBody::setDirection(const Dir4 dir)
{
    switch (dir) {
        case Dir4::left:  { moving_left  = 1; body->updateFacing(dir); break; }
        case Dir4::right: { moving_right = 1; body->updateFacing(dir); break; }
        default: { break; }
    }
}
void RigidBody::stopDirection(const Dir4 dir)
{
    switch (dir) {
        case Dir4::left: { moving_left = 0; break; }
        case Dir4::right: { moving_right = 0; break; }
        default: { break; }
    }
}
void RigidBody::jump()
{
    if (cur_state == ObjectState::idle || cur_state == ObjectState::running) {
        vel.y -= f_jump;
    }
}
void RigidBody::terminateJump()
{

}
void RigidBody::onColliding(const sf::Vector2f offset, ColliderType type)
{
    if (fabs(offset.x) < fabs(offset.y)) {
        body->xCollision(offset.x);
        vel.x = 0.f;
    } else {
        if (cur_state == ObjectState::jumping) {
            vel.y = 0.f;
            if (offset.y > 0.f) {
                body->yCollision(offset.y);
                // idea -- x velocity takes a hit for 'friction' ?
            } else {
                cur_state = ObjectState::falling;
            }
        } else {
            body->yCollision(offset.y);
            if (type == ColliderType::body) {
                vel.y = 0.f;
            }
        }
    }
}
const ObjectState RigidBody::getState() const
{
    ObjectState next_state = cur_state;
    switch (cur_state) {
        case ObjectState::jumping: {
            if (vel.y >= 0.f) {
                next_state = ObjectState::falling;
            }
            break;
        }
        case ObjectState::falling: {
            if (vel.y <= 0.f) {
                if (moving_right - moving_left) {
                    next_state = ObjectState::running;
                } else {
                    next_state = ObjectState::idle;
                }
            } else {
                next_state = ObjectState::falling;
            }
            // else if wall sliding
            break;
        }
        case ObjectState::wallsliding: {

        }
        default: { // covers running or idle
            if (moving_right - moving_left) {
                next_state = ObjectState::running;
            } else {
                next_state = ObjectState::idle;
            }
            if (vel.y < 0.f) {
                next_state = ObjectState::jumping;
            } else if (vel.y > 1.5f) {
                next_state = ObjectState::falling;
            }

            break;
        }
    }
    return next_state;
}
void RigidBody::setCollisionRects(const std::vector<CollisionRect>& rects)
{
    body->setColliders(rects);
}
const sf::Vector2f RigidBody::getPosition() const
{
    return body->getPosition();
}
const sf::Vector2f RigidBody::getVelocity() const
{
    return vel;
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
