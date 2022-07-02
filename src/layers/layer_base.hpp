#ifndef LYR_BASE_HPP
#define LYR_BASE_HPP

#include "../common.hpp"
#include "layer_assets.hpp"

class LayerBase
{
public:
    LayerBase(const LayerAssetBase& ast);
    ~LayerBase();

protected:
    const int order;
    const std::string name;
};

#endif // LYR_BASE_HPP
