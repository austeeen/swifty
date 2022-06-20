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
    const PhysicsCoeffs coeffs;
    std::map<ObjectState, std::shared_ptr<AnimRoll>> animation_rolls;
};

#endif // DATA_HPP
