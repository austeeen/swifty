#ifndef LYR_OBJ_HPP
#define LYR_OBJ_HPP

#include "layer_base.hpp"
#include "../tiled/tileset.hpp"

class ObjectLayer: public LayerBase
{
public:
    ObjectLayer(const TileLayerAsset& ast);
    ~ObjectLayer();

private:
    const ObjectLayerAsset ast;
    std::vector<sf::IntRect> objects;
};

/**************************************************************************************************/

struct DynamicObjectGroup: public LayerBase
{
    DynamicObjectGroup(rx::xml_node<>* node);
    void build(const std::map<const int, TileSet*>& tilesets);

    std::map<std::string, std::shared_ptr<DynamicTiledObject>> objects;
    std::map<int, Waypoint> waypoints;
};

/**************************************************************************************************/

struct SpawnLocations: public LayerBase
{
    SpawnLocations(rx::xml_node<>* node);

    std::map<std::string, sf::IntRect> to_spawn;
};

/**************************************************************************************************/

struct AiZones: public LayerBase
{
    AiZones(rx::xml_node<>* node);
    std::map<std::string, sf::IntRect> all_zones;
};


#endif // LYR_OBJ_HPP
