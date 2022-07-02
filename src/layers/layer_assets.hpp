#ifndef LYR_ASSET_HPP
#define LYR_ASSET_HPP

#include "../common.hpp"
#include "../utils/rect.hpp"

struct LayerAssetBase
{
    int order;
    std::string name;
};

struct TileLayerAsset: public LayerAssetBase
{
    int width, height;
    std::string tilestr;
};

struct ObjectLayerAsset: public LayerAssetBase
{
    std::map<const int, LayerObjectAsset> tiledata;
};

#endif // LYR_ASSET_HPP
