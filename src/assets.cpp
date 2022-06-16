#include "assets.hpp"

GameObjectAsset::GameObjectAsset(const TileObject& obj):
    img_texture(obj.img_texture),
    size(obj.tilesize),
    rect(sf::Vector2f(0, 0), (sf::Vector2f) obj.tilesize),
    collision_rect(sf::Vector2f(0, 0), (sf::Vector2f) obj.tilesize),
    speed(obj.speed),
    mass(obj.mass),
    max_x_vel(obj.max_x_vel),
    jump_power(obj.jump_power),
    acl_gravity(obj.acl_gravity),
    damping(obj.damping),
    animation_rolls(obj.animation_rolls)
{
     start_pos = sf::Vector2f(CAT_START_X * obj.tilesize.x, CAT_START_Y * obj.tilesize.y);
}
