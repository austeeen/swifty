#include "moving_platform.hpp"

MovingPlatform::MovingPlatform(const PlatformObjectAsset& ast):
    ast(ast),
    sprite(nullptr),
    collider(ast.collider),
    position_rect(ast.position_rect),
    vel(0, 0), cur_dest(0, 0),
    display_body(false), waypoint_indx(0), total_waypoints(ast.waypoints.size())
{
    pos_shape.setOutlineThickness(1);
    pos_shape.setFillColor(sf::Color::Transparent);
    pos_shape.setOutlineColor(sf::Color::Green);

    col_shape.setOutlineThickness(1);
    col_shape.setFillColor(sf::Color::Transparent);
    col_shape.setOutlineColor(sf::Color::Blue);

    sprite = new sf::Sprite(ast.img_texture);
}
MovingPlatform::~MovingPlatform()
{
    delete sprite;
    sprite = nullptr;
}
void MovingPlatform::setUp()
{
    cur_dest = ast.waypoints[waypoint_indx];
    printf("set up) start pos: (%f, %f)\n", ast.start_pos.x, ast.start_pos.y);
    printf("set up) my pos: (%f, %f)\n", position_rect.left, position_rect.top);
}
void MovingPlatform::update(const float dt)
{
    float mx = position_rect.left;
    float my = position_rect.top;
    const float dx = mx - cur_dest.x;
    const float dy = my - cur_dest.y;


    if (fabs(dx) < 0.01f) {
        mx = cur_dest.x;
    }
    else if (dx > 0) {
        vel.x = -ast.speed;
    } else {
        vel.x = ast.speed;
    }

    if (fabs(dy) < 0.01f) {
        my = cur_dest.y;
    }
    else if (dy > 0) {
        vel.y = -ast.speed;
    } else {
        vel.y = ast.speed;
    }

    if (mx == cur_dest.x && my == cur_dest.y) {
        nextDestination();
    }

    // printf("platform: v(%f, %f)\n", vel.x, vel.y);

    move(vel.x * dt, vel.y * dt);
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
void MovingPlatform::toggleDisplay()
{
    display_body = !display_body;
}
void MovingPlatform::nextDestination()
{
    if (cur_dest == ast.start_pos) {
        waypoint_indx = (waypoint_indx + 1) % total_waypoints;
        cur_dest = ast.waypoints[waypoint_indx];
        std::cout << "waypoint #" << waypoint_indx << std::endl;
    } else {
        cur_dest = ast.start_pos;
        std::cout << "start pos" << std::endl;
    }
    std::cout << cur_dest.x << ", " << cur_dest.y << std::endl;
    printf("nextDest) my pos: (%f, %f)\n", position_rect.left, position_rect.top);
}
const CollisionRect& MovingPlatform::getCollider() const
{
    return collider;
}
const sf::Vector2f& MovingPlatform::getVelocity() const
{
    return vel;
}
