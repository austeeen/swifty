#include "rigid_body.hpp"
#include "../objects/game_object.hpp"

RigidBody::RigidBody(GameObject* obj):
    Component(obj),
    cur_facing(Dir4::right),
    m_body_collider(nullptr),
    display_body(false)
{}
void RigidBody::setUp()
{
    GameObjectAsset ast = obj->getAsset();
    position_rect = sf::FloatRect(0, 0, ast.size.x, ast.size.y);
    pos_shape = createShape(sf::Color::Green);
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
    m_body_collider = nullptr;
    for (auto& col_rect : rects) {
        collision_rects.push_back(col_rect);
        if (col_rect.type == ColliderType::body) {
            m_body_collider = &collision_rects.back();
        }
    }
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
bool RigidBody::overlapping(const sf::FloatRect& rect) const
{
    return m_body_collider->aabb.intersects(rect);
}
bool RigidBody::intersects(const sf::Vector2f& loc) const
{
    return position_rect.contains(loc);
}
bool RigidBody::intersects(const sf::FloatRect& rect) const
{
    return position_rect.intersects(rect);
}
bool RigidBody::closeTo(const sf::Vector2f& loc) const
{
    // todo -- grow size of body collider by some amount (1.5x, 2x, etc)
    return position_rect.contains(loc);
}
bool RigidBody::closeTo(const sf::FloatRect& rect) const
{
    // todo -- grow size of body collider by some amount (1.5x, 2x, etc)
    return position_rect.intersects(rect);
}
const sf::Vector2f RigidBody::getPosition() const
{
    return sf::Vector2f(position_rect.left, position_rect.top);
}
const sf::FloatRect& RigidBody::getPositionRect() const
{
    return position_rect;
}
const sf::Vector2i RigidBody::getSize() const
{
    return sf::Vector2i(position_rect.width, position_rect.height);
}
const std::vector<CollisionRect>& RigidBody::getColliders() const
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
