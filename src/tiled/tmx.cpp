#include "tmx.hpp"

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
        printf("<%s ...> \n", type.c_str());
        if (type == "tileset") {
            int firstgid = attr<int>(node, "firstgid");
            tilesets[firstgid] = new TileSet(node);
        }
        else if (type == "layer") {
            tile_layers.push_back(new TileLayer(node));
        }
        else if (type == "objectgroup") {
            std::string sub_type = attr<std::string>(node, "name");
            if (sub_type == "dynamic") {
                dyn_object_groups.push_back(new DynamicObjectGroup(node));
            } else {
                object_groups.push_back(new ObjectGroup(node));
            }
        }
        node = node->next_sibling();
    }
    delete doc;
}
TileMap::~TileMap()
{
    for (auto& [gid, ts] : tilesets) {
        delete ts;
    }
    tilesets.clear();

    for (auto& tl : tile_layers) {
        delete tl;
    }
    tile_layers.clear();

    for (auto& og : object_groups) {
        delete og;
    }
    object_groups.clear();

    for (auto& dog : dyn_object_groups) {
        delete dog;
    }
    dyn_object_groups.clear();
}
void TileMap::build()
{
    for (auto& lyr : tile_layers) {
        lyr->build(this);
    }
    for (auto& lyr : dyn_object_groups) {
        lyr->build(this);
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
