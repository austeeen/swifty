#ifndef AST_LAYERS_HPP
#define AST_LAYERS_HPP

#include "asset_core.hpp"
#include "objects.hpp"

struct LayerAssetBase: Asset
{
    LayerAssetBase(Layer* lyr_res);
    int r_order;
    LayerType type;
};

struct TileLayerAsset: LayerAssetBase
{
    TileLayerAsset(TileLayer* lyr_res);
    sf::RenderTexture* render_texture;
};

struct BoundaryLayerAsset: LayerAssetBase
{
    BoundaryLayerAsset(ObjectLayer* lyr_res);
    std::vector<sf::IntRect> objects;
};

struct PlatformLayerAsset: LayerAssetBase
{
    PlatformLayerAsset(ObjectLayer* lyr_res);
    std::map<std::string, std::shared_ptr<PlatformObjectAsset>> objects;
    std::map<int, Waypoint> waypoints;
};

struct GameObjectLayerAsset: LayerAssetBase
{
    GameObjectLayerAsset(ObjectLayer* lyr_res);
    std::map<std::string, std::shared_ptr<GameObjectLayerAsset>> objects;
    std::map<int, Waypoint> waypoints;
};


#endif // AST_LAYERS_HPP
