#ifndef TLD_LOCATIONS_LAYER_HPP
#define TLD_LOCATIONS_LAYER_HPP

#include "tiled_core.hpp"

class TileMap;

struct Locations
{
    Locations(rx::xml_node<>* node);
    std::map<std::string, sf::IntRect> location_table;
};

struct AiZones
{
    AiZones(rx::xml_node<>* node);
    void build(TileMap* map);
    std::map<std::string, sf::IntRect> all_zones;
};

#endif // TLD_LOCATIONS_LAYER_HPP
