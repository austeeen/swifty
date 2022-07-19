#ifndef TLD_TILEMAP_HPP
#define TLD_TILEMAP_HPP

#include <tiledbytes.hpp>
#include "../common.hpp"

#include "tileset.hpp"
#include "tsx.hpp"
#include "tile_layer.hpp"
#include "locations_layer.hpp"
#include "structure_layers.hpp"

class Level
{
public:
    Level(const char* filepath);
    ~Level();
    void build();
    TileSet* getTileset(const int cur_gid);

private:
    void addStructures(rx::xml_node<>* node);

    std::map<const int, TileSet*> tilesets;
    TileLayer* background;
    Locations* locations;
    std::map<const std::string, StructureLayer*> structure_group;
    sf::Vector2i mapsize, tilesize;
};

#endif // TLD_TILEMAP_HPP
