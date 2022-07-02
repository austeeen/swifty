#include "scenes.hpp"

SceneAsset::SceneAsset(TileMap *map):
    Asset(map->name)
{
    mapsize = map->mapsize;
    tilesize = map->tilesize;

    for (auto& [lyr_str, lyr_res] : map->tilelayers) {
        layers.tile[lyr_str] = new TileLayerAsset(lyr_res);
    }
    for (auto& [lyr_str, lyr_res] : map->objectlayers) {
        switch(Layer::asType.at(lyr_str)) {
            case Layer::type::BOUNDARY: {
                layers.boundary[lyr_str] = new BoundaryLayerAsset(lyr_res);
                break;
            }
            case Layer::type::PLATFORM: {
                layers.platform[lyr_str] = new PlatformLayerAsset(lyr_res);
                break;
            }
            case Layer::type::OBJECT: {
                layers.gameobject[lyr_str] = new GameObjectLayerAsset(lyr_res);
                break;
            }
            default: { break; }
        }
    }
}
void SceneAsset::build(Foundry* foundry)
{

}
