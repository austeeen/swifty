#include "moving_platform.hpp"

MovingPlatform::MovingPlatform(const PlatformObjectAsset& ast):
    ast(ast),
    sprite(nullptr),
    collider(ast.collider),
    position_rect(ast.position_rect),
    vel(0, 0), cur_dest(0, 0),
    display_body(false)
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
    // move(ast.start_pos.x, ast.start_pos.y);
    cur_dest = ast.dest;
    printf("set up start pos: (%f, %f)\n", ast.start_pos.x, ast.start_pos.y);
    sf::FloatRect sz = sprite->getGlobalBounds();
    printf("  sprite rect: (%f, %f, %f, %f)\n", sz.left, sz.top, sz.width, sz.height);
    printf("  pos    rect: (%f, %f, %f, %f)\n", position_rect.left, position_rect.top, position_rect.width, position_rect.height);
    printf("  aabb   rect: (%f, %f, %f, %f)\n", collider.aabb.left, collider.aabb.top, collider.aabb.width, collider.aabb.height);
}
void MovingPlatform::update(const float dt)
{
    float mx = position_rect.left;
    float my = position_rect.top;
    const float dx = mx - cur_dest.x;
    const float dy = my - cur_dest.y;

    // printf("pos: (%f, %f), disp: (%f, %f)\n", mx, my, dx, dy);

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
        if (cur_dest == ast.dest) {
            cur_dest = ast.start_pos;
        } else {
            cur_dest = ast.dest;
        }
    }
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
const CollisionRect& MovingPlatform::getCollider() const
{
    return collider;
}
