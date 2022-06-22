#ifndef ASSETS_HPP
#define ASSETS_HPP

#include "common.hpp"
#include "tiled/all.hpp"

#define CAT_START_X 1
#define CAT_START_Y 1

struct GameObjectAsset
{
    GameObjectAsset(std::shared_ptr<TsxBaseObject> tsx_obj);
    sf::Vector2f start_pos;
    const sf::Texture img_texture;
    const sf::Vector2i size;
};

struct PlayerObjectAsset: public GameObjectAsset
{
    PlayerObjectAsset(std::shared_ptr<TileObject> tsx_obj);

    const PhysicsCoeffs coeffs;
    std::map<ObjectState, std::shared_ptr<AnimRoll>> animation_rolls;
};

struct PlatformObjectAsset: public GameObjectAsset
{
    PlatformObjectAsset(std::shared_ptr<DynamicTiledObject> tsx_obj);

    const CollisionRect collider;
    const int speed;
    const sf::Vector2f dest;
    bool horizontal;
};

#endif // ASSETS_HPP
