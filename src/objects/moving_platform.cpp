#include "moving_platform.hpp"

MovingPlatform::MovingPlatform(const PlatformObjectAsset& ast):
    ast(ast),
    sprite(nullptr),
    collider(ast.collider),
    position_rect(ast.position_rect),
    vel(0, 0),
    traversing(true),
    display_body(false)
{
    pos_shape.setOutlineThickness(1);
    pos_shape.setFillColor(sf::Color::Transparent);
    pos_shape.setOutlineColor(sf::Color::Green);

    col_shape.setOutlineThickness(1);
    col_shape.setFillColor(sf::Color::Transparent);
    col_shape.setOutlineColor(sf::Color::Blue);

    sprite = new sf::Sprite(ast.img_texture);
    wp = ast.root_waypoint;
}
MovingPlatform::~MovingPlatform()
{
    delete sprite;
    sprite = nullptr;
    wp = nullptr;
}
void MovingPlatform::setUp()
{
    wp = wp->next;
}
void MovingPlatform::update(const float dt)
{
    const float dx = position_rect.left - wp->loc.x;
    const float dy = position_rect.top - wp->loc.y;
    float new_vx = 0.f;
    float new_vy = 0.f;

    if (dx != 0.f) {
        if (fabs(dx) < FLT_ZERO) {
            position_rect.left = wp->loc.x;
            vel.x = 0;
        } else if (dx > 0) {
            vel.x = -ast.speed;
            new_vx = vel.x * dt;

            float next_dx = (position_rect.left + new_vx) - wp->loc.x;
            if (next_dx < 0) {
                // out::debug(ast.name.c_str(), "overshoot X axis stopped!");
                position_rect.left = wp->loc.x;
                vel.x = 0;
                new_vx= 0;
            }
        } else {
            vel.x = ast.speed;
            new_vx = vel.x * dt;

            float next_dx = (position_rect.left + new_vx) - wp->loc.x;
            if (next_dx > 0) {
                // out::debug(ast.name.c_str(), "undershoot X axis stopped!");
                position_rect.left = wp->loc.x;
                vel.x = 0;
                new_vx= 0;
            }
        }
    }

    if (dy != 0.f) {
        if (dy > 0) {
            vel.y = -ast.speed;
            new_vy = vel.y * dt;

            // check for overshooting the waypoint position, consider this object there already if 
            // so.
            float next_dy = (position_rect.top + new_vy) - wp->loc.y;
            if (next_dy < 0) {
                // out::debug(ast.name.c_str(), "overshoot Y axis stopped!");
                position_rect.top = wp->loc.y;
                vel.y = 0;
                new_vy = 0;
            }
        } else {
            vel.y = ast.speed;
            new_vy = vel.y * dt;

            // check for overshooting the waypoint position, consider this object there already if 
            // so.
            float next_dy = (position_rect.top + new_vy) - wp->loc.y;
            if (next_dy > 0) {
                // out::debug(ast.name.c_str(), "undershoot Y axis stopped!");
                position_rect.top = wp->loc.y;
                vel.y = 0;
                new_vy = 0;
            }
        }
    }

    move(new_vx, new_vy);
}
void MovingPlatform::lateUpdate()
{
    if (position_rect.left == wp->loc.x && position_rect.top == wp->loc.y) {
        nextWaypoint();
    }
}
void MovingPlatform::render(sf::RenderWindow &window)
{
    sprite->setTexture(ast.img_texture);
    sprite->setPosition(position_rect.left, position_rect.top);
    window.draw(*sprite);

    if (display_body) {
        pos_shape.setPosition(position_rect.left, position_rect.top);
        pos_shape.setSize(sf::Vector2f(position_rect.width, position_rect.height));

        col_shape.setPosition(collider.aabb.left, collider.aabb.top);
        col_shape.setSize(sf::Vector2f(collider.aabb.width, collider.aabb.height));

        window.draw(pos_shape);
        window.draw(col_shape);
    }
}
void MovingPlatform::move(const float dx, const float dy)
{
    position_rect.left += dx;
    position_rect.top += dy;
    collider.aabb.left = position_rect.left + collider.offset.x;
    collider.aabb.top = position_rect.top + collider.offset.y;
}
void MovingPlatform::toggleDisplay(const int opt)
{
    if (opt == -1) {
        display_body = !display_body;    
    } else if (opt == 0) {
        display_body = false;
    } else {
        display_body = true;
    }
}
void MovingPlatform::nextWaypoint()
{

    if(wp->next == nullptr) {
        traversing = false;
    } else if (wp->prev == nullptr) {
        traversing = true;
    }

    if (traversing) {
        wp = wp->next;
    } else {
        wp = wp->prev;
    }
}
const CollisionRect& MovingPlatform::getCollider() const
{
    return collider;
}
const sf::Vector2f& MovingPlatform::getVelocity() const
{
    return vel;
}
