#ifndef LYR_TILE_HPP
#define LYR_TILE_HPP

#include "layer_base.hpp"
#include "../tiled/tileset.hpp"


class TileLayer: public LayerBase
{
public:
    TileLayer(const TileLayerAsset& ast);
    ~TileLayer();
    void build(const std::map<const int, TileSet*>& tilesets);

private:
    const TileLayerAsset ast;
    sf::VertexArray vertex_array;
    sf::RenderTexture* render_texture;
};

#endif // LYR_TILE_HPP
