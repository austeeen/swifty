#ifndef ASSETS_HPP
#define ASSETS_HPP

#include <SFML/Graphics.hpp>
#include "typedef.hpp"

#define CAT_WIDTH 16
#define CAT_HEIGHT 16

struct GameObjectAsset
{

    const std::string img_fp = "res/elthen/cat-16x16.png";
    const sf::IntRect start_texture_rect = sf::IntRect(0, 0, CAT_WIDTH, CAT_HEIGHT);
    const sf::Vector2f start_pos = sf::Vector2f(150, 200 - CAT_HEIGHT - 1);
    const sf::Vector2i size = sf::Vector2i(CAT_WIDTH, CAT_HEIGHT);
    const sf::FloatRect rect = sf::FloatRect(start_pos, (sf::Vector2f) size);
    const sf::FloatRect collision_rect = sf::FloatRect(CAT_WIDTH - 12 - 1, CAT_HEIGHT - 10 - 1, 12, 10);
    const int speed = 4; // * 100
    const int mass = 10;
    const int max_x_vel = 100;
    const int jump_power = 13; // * 100
    const float acl_gravity = 35;  // P/sec^2 where 1 P ~= 16 pixels
    const float friction = 2;  // frictional coefficient -- made up surface friction value
    // const float damping = 2.0f;

    // from cat.png
    const animconfig idle_cfg {  0, 8, 0.1f };
    const animconfig moving_cfg { 1, 5, 0.1f };
    const animconfig jumping_cfg { 2, 4, 0.12f, {}, true, true, 2 };
};

#endif // DATA_HPP
