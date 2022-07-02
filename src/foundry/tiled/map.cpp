#include "map.hpp"

TileMap::TileMap(const char* filepath)
{
    rx::xml_document<>* doc = new rx::xml_document<>();
    std::string content = "";
    loadXML(filepath, content, doc);
    if (doc == nullptr || content == "") {
        std::cout << "tile map construction failed" << std::endl;
        return;
    }
}
TileMap::~TileMap()
{
    utl::destroy(doc);
    utl::destroy(content);
    utl::destroy(tilesets);
    utl::destroy(tilelayers);
    utl::destroy(objectlayers);
}
void TileMap::process()
{

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
        } else if (type == "layer") {
            tilelayers[attr<std::string>(node, "name")] = new TileLayer(node);
        } else if (type == "objectgroup") {
            objectlayers[attr<std::string>(node, "name")] = new ObjectLayer(node);
        }
        node = node->next_sibling();
    }

    for (auto &tl : tilelayers) {
        tl->process(this);
    }
    for (auto &ol : objectlayers) {
        ol->process(this);
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
sf::Vector2i TileMap::getTileSize() const
{
    return tilesize;
}
