#ifndef ASSETS_HPP
#define ASSETS_HPP

#include "common.hpp"
#include "rsrc_tiled.hpp"

#define CAT_START_X 1
#define CAT_START_Y 1

struct GameObjectAsset
{
    GameObjectAsset(const TileObject& obj);
    sf::Vector2f start_pos;
    const sf::Texture img_texture;
    const sf::Vector2i size;
    const sf::FloatRect rect;
    const int speed; // * 100
    const int mass;
    const int max_x_vel;
    const int jump_power; // * 100
    const float acl_gravity;  // P/sec^2 where 1 P ~= 16 pixels
    const float damping;
    std::map<ObjectState, std::shared_ptr<AnimRoll>> animation_rolls;
};

#endif // DATA_HPP
