#ifndef AST_SCENE_HPP
#define AST_SCENE_HPP

#include "asset_core.hpp"
#include "layers.hpp"

class Foundry;

struct SceneAsset: Asset
{
    SceneAsset(TileMap* map_res);
    void build(Foundry* foundry);

private:
    sf::Vector2i mapsize, tilesize;

    struct Layers {
        std::map<std::string, TileLayerAsset*> tile;
        std::map<std::string, BoundaryLayerAsset*> boundary;
        std::map<std::string, PlatformLayerAsset*> platform;
        std::map<std::string, GameObjectLayerAsset*> gameobject;
    } layers;
};

#endif // AST_SCENE_HPP
