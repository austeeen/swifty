#include "structure_layers.hpp"
#include "tile_map.hpp"

StructureLayer::StructureLayer(rx::xml_node<> *node)
{
    name = attr<std::string>(node, "name");
    id = attr<int>(node, "id");
}

/**************************************************************************************************/

StaticStructures::StaticStructures(rx::xml_node<> *node):
    StructureLayer(node)
{
    tld::getRects(node, all_rects);
    // TODO: trace out walls and merge them
}
void StaticStructures::build(TileMap *map)
{
    // TODO: use tld::Rect to get the rect's tileset entry for texture/collision stuff
    for (auto& r: all_rects) {
        // TODO: implement tracer agent for combining basic rects
    }
}
StaticStructures::~StaticStructures()
{
    for (auto& r: all_rects) {
        delete r;
    }
    all_rects.clear();
}

/**************************************************************************************************/

DynamicStructures::DynamicStructures(rx::xml_node<> *node):
    StructureLayer(node)
{
    rx::xml_node<> *obj = node->first_node();
    while (obj != nullptr) {

        int next_id = -1;
        rx::xml_node<> *prps = obj->first_node("properties");
        if (prps != nullptr) {
            std::map<std::string, std::string> prp_tbl;
            tld::extractProperties(prps, prp_tbl);
            if (prp_tbl.count("next") != 0) {
                next_id = std::stoi(prp_tbl.at("next"));
            }
        }

        waypoints[attr<int>(obj, "id")] = Waypoint {
            sf::Vector2f(attr<int>(obj, "x"), attr<int>(obj, "y")), next_id
        };

        if (attr_if<std::string>(obj, "class") == "platform") {
            objects[attr<int>(obj, "id")] = new tld::Rect(obj);
        }
        obj = obj->next_sibling();
    }
}
DynamicStructures::~DynamicStructures()
{
    for (auto& [id, obj] : objects) {
        delete obj;
    }
    objects.clear();
}
void DynamicStructures::build(TileMap *map)
{
    // TODO: use tld::Rect to get the rect's tileset entry for texture/collision stuff
    for (auto& [id, dyn_obj] : objects) {
        // TODO: reimplement using tracer agent
        // dyn_obj->combinePieces(map);
        // dyn_obj->setWaypointTree(waypoints);
    }
}

/**************************************************************************************************/

TerrainStructures::TerrainStructures(rx::xml_node<> *node):
    StructureLayer(node)
{
    tld::getRects(node, objects);
}
void TerrainStructures::build(TileMap *map)
{
    // TODO: use tld::Rect to get the rect's tileset entry for texture/collision stuff
    for (auto& [id, dyn_obj] : objects) {
        // TODO: implement tracer agent for terrain types
    }
}
TerrainStructures::~TerrainStructures()
{
    for (auto& [id, obj] : objects) {
        delete obj;
    }
    objects.clear();
}
