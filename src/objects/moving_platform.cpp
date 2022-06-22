#include "moving_platform.hpp"

MovingPlatform::MovingPlatform(const PlatformObjectAsset& ast):
    ast(ast),
    collider(ast.collider),
    position_rect(ast.start_pos.x, ast.start_pos.y, ast.size.x, ast.size.y),
    vel(0, 0), cur_dest(0, 0), display_body(false)
{
    sprite.setTexture(ast.img_texture);
    sprite.setPosition(ast.start_pos);
}
void MovingPlatform::setUp()
{
    move(ast.start_pos.x, ast.start_pos.y);
    cur_dest = ast.dest;
    printf("set up start pos: (%f, %f)\n", ast.start_pos.x, ast.start_pos.y);
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
        vel.x = ast.speed;
    } else {
        vel.x = -ast.speed;
    }

    if (fabs(dy) < 0.01f) {
        my = cur_dest.y;
    }
    else if (dy > 0) {
        vel.y = ast.speed;
    } else {
        vel.y = -ast.speed;
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
    sprite.setPosition(position_rect.left, position_rect.top);
    window.draw(sprite);

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
