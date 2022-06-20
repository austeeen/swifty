#include "rigid_body.hpp"
#include "../objects/player.hpp"

RigidBody::RigidBody(Player* obj):
    Component(obj),
    cur_facing(Dir4::right),
    display_body(false)
{}
void RigidBody::setUp()
{
    GameObjectAsset ast = obj->getAsset();
    position_rect = ast.rect;
    pos_shape = createShape(sf::Color::Green);
    move(ast.start_pos.x, ast.start_pos.y);
}
void RigidBody::render(sf::RenderWindow &window)
{
    if (!display_body) {
        return;
    }

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
void RigidBody::toggleDisplay()
{
    display_body = !display_body;
}
void RigidBody::setColliders(const std::vector<CollisionRect>& rects)
{
    collision_rects.clear();
    copy(rects.begin(), rects.end(), back_inserter(collision_rects));
    if (cur_facing == Dir4::left) {
        faceLeft();
    }
    updateColliders();
}
void RigidBody::move(const float x, const float y)
{
    position_rect.left += x;
    position_rect.top += y;
    updateColliders();
}
void RigidBody::updateFacing(const Dir4 next_facing)
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
void RigidBody::updateColliders()
{
    for (auto& col_rect : collision_rects) {
        col_rect.aabb.left = position_rect.left + col_rect.offset.x;
        col_rect.aabb.top = position_rect.top + col_rect.offset.y;
    }
}
void RigidBody::faceLeft()
{
    for (auto& col_rect : collision_rects) {
        col_rect.offset.x = position_rect.width - col_rect.aabb.width - col_rect.offset.x;
    }
}
void RigidBody::faceRight()
{
    for (auto& col_rect : collision_rects) {
        col_rect.offset.x = position_rect.width - (col_rect.offset.x + col_rect.aabb.width);
    }
}
void RigidBody::xCollision(const float offset)
{
    position_rect.left += offset;
    for (auto& col_rect : collision_rects) {
        col_rect.aabb.left += offset;
    }
}
void RigidBody::yCollision(const float offset)
{
    position_rect.top += offset;
    for (auto& col_rect : collision_rects) {
        col_rect.aabb.top += offset;
    }
}
const sf::Vector2f RigidBody::getPosition() const
{
    return sf::Vector2f(position_rect.left, position_rect.top);
}
const sf::Vector2i RigidBody::getSize() const
{
    return sf::Vector2i(position_rect.width, position_rect.height);
}
const std::vector<CollisionRect>& RigidBody::getRects() const
{
    return collision_rects;
}
sf::RectangleShape RigidBody::createShape(sf::Color c)
{
    sf::RectangleShape shape;
    shape.setOutlineThickness(1);
    shape.setFillColor(sf::Color::Transparent);
    shape.setOutlineColor(c);
    return shape;
}
