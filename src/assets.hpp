#ifndef ASSETS_HPP
#define ASSETS_HPP

#include "common.hpp"
#include "tiled/all.hpp"

#define CAT_START_X 1
#define CAT_START_Y 1

struct ObjectAssetBase
{
    ObjectAssetBase(std::shared_ptr<TsxBaseObject> tsx_obj);

    sf::Vector2f start_pos;
    sf::Texture img_texture;
    const sf::Vector2i size;
};

struct GameObjectAsset: public ObjectAssetBase
{
    GameObjectAsset(std::shared_ptr<TileObject> tsx_obj);

    const std::string name;
    const bool facing_right;
    const PhysicsCoeffs coeffs;
    std::map<ObjectState, std::shared_ptr<AnimRoll>> animation_rolls;
};

struct PlatformObjectAsset: public ObjectAssetBase
{
    PlatformObjectAsset(std::shared_ptr<DynamicTiledObject> tsx_obj);

    const std::string name;
    const sf::FloatRect position_rect;
    const CollisionRect collider;
    const int speed;
    Waypoint* root_waypoint;
};

#endif // ASSETS_HPP
