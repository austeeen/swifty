#include "tile_map.hpp"

TileMap::TileMap(const char* filepath)
{
    rx::xml_document<>* doc = new rx::xml_document<>();
    std::string content = "";
    loadXML(filepath, content, doc);
    if (doc == nullptr || content == "") {
        std::cout << "tile map construction failed" << std::endl;
        return;
    }
    rx::xml_node<> *map = doc->first_node();
    mapsize.x = attr<int>(map, "width");
    mapsize.y = attr<int>(map, "height");
    tilesize.x = attr<int>(map, "tilewidth");
    tilesize.y = attr<int>(map, "tileheight");
    rx::xml_node<> *node = map->first_node();
    while(node != nullptr) {
        std::string type = std::string(node->name());
        if (type == "tileset") {
            tilesets[attr<int>(node, "firstgid")] = new TileSet(node);
        } else {
            std::string sub_type = attr<std::string>(node, "name");
            if (sub_type == "location") {
                locations = new Locations(node);
            } else if (sub_type == "background") {
                background = new TileLayer(node);
            } else if (sub_type == "structures") {
                addStructures(node);
            }
        }
        node = node->next_sibling();
    }
    delete doc;
}
TileMap::~TileMap()
{
    delete background;
    background = nullptr;
    delete locations;
    locations = nullptr;

    for (auto& [gid, ts] : tilesets) {
        delete ts;
    }
    tilesets.clear();

    for (auto& [name, st] : structure_group) {
        delete st;
    }
    structure_group.clear();
}
void TileMap::build()
{
    background->build(this);
    for (auto& [name, st] : structure_group) {
        st->build(this);
    }
}
TileSet* TileMap::getTileset(const int cur_gid)
{
    int indx = 0; // arbitrary number
    for (auto [ts_gid, ts] : tilesets) {
        if (cur_gid >= ts_gid) {
            if (indx < ts_gid) {
                indx = ts_gid;
            }
        }
    }
    return tilesets[indx];
}
void TileMap::addStructures(rx::xml_node<>* node)
{
    rx::xml_node<> *lyr_node = node->first_node();
    while(lyr_node) {
        std::string type = std::string(lyr_node->name());
        if (type == "dynamic") {
            structure_group[type] = new DynamicStructures(lyr_node);
        }
        else if (type == "static") {
            structure_group[type] = new StaticStructures(lyr_node);
        }
        else if (type == "terrain") {
            structure_group[type] = new TerrainStructures(lyr_node);
        }
        node = node->next_sibling();
    }
}
