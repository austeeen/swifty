#ifndef TLD_TMX_HPP
#define TLD_TMX_HPP

#include "../utils/utils.hpp"
#include "tileset.hpp"
#include "tsx.hpp"
#include "layers.hpp"

class TileMap
{
public:
    TileMap(const char* filepath);
    ~TileMap();
    void build();
    TileSet* getTileset(const int cur_gid);

    std::map<const int, TileSet*> tilesets;
    std::vector<TileLayer*> tile_layers;
    std::vector<ObjectGroup*> object_groups;
    std::vector<DynamicObjectGroup*> dyn_object_groups;
    SpawnLocations* spawn_locations;
    
    sf::Vector2i mapsize, tilesize;
};

#endif // TLD_TMX_HPP
