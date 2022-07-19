#ifndef TLD_TILE_LAYER_HPP
#define TLD_TILE_LAYER_HPP

#include "tiled_core.hpp"

class TileMap;

class TileLayer
{
public:
    TileLayer(rx::xml_node<>* node);
    ~TileLayer();
    void build(TileMap* map);

private:
    std::string name;
    int id;
    std::string gidstr;
    sf::Vector2i size;
    sf::VertexArray vertex_array;
    sf::RenderTexture* render_texture;
};

#endif // TLD_TILE_LAYER_HPP
