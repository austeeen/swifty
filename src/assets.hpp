#ifndef ASSETS_HPP
#define ASSETS_HPP

#include "common.hpp"
#include "typedef.hpp"
#include "rsrc_tiled.hpp"

#define CAT_WIDTH 16
#define CAT_HEIGHT 16

#define CAT_START_X 3
#define CAT_START_Y 2

struct GameObjectAsset
{
    GameObjectAsset(const ObjectConfig& cfg);

    const std::string img_fp = "res/elthen/cat-16x16.png";
    const sf::IntRect start_texture_rect = sf::IntRect(0, 0, CAT_WIDTH, CAT_HEIGHT);
    const sf::Vector2f start_pos = sf::Vector2f(CAT_START_X * CAT_WIDTH, CAT_START_Y * CAT_HEIGHT);
    const sf::Vector2i size = sf::Vector2i(CAT_WIDTH, CAT_HEIGHT);
    const sf::FloatRect rect = sf::FloatRect(start_pos, (sf::Vector2f) size);
    const sf::FloatRect collision_rect = sf::FloatRect(CAT_WIDTH - 12 - 1, CAT_HEIGHT - 10 - 1, 12, 10);
    const int speed; // * 100
    const int mass;
    const int max_x_vel;
    const int jump_power; // * 100
    const float acl_gravity;  // P/sec^2 where 1 P ~= 16 pixels
    const float damping;

    // from cat.png
    const animconfig idle_cfg {  0, 8, 0.1f };
    const animconfig moving_cfg { 1, 5, 0.1f };
    const animconfig jumping_cfg { 2, 4, 0.12f, {}, true, true, 2 };
};

#endif // DATA_HPP
