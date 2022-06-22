#include "tileset.hpp"

TileSet::TileSet(rx::xml_node<> *node)
{
    name = attr<std::string>(node, "name");
    firstgid = attr<int>(node, "firstgid");
    tilesize.x = attr<int>(node, "tilewidth");
    tilesize.y = attr<int>(node, "tileheight");
    totaltiles = attr<int>(node, "tilecount");
    columns = attr<int>(node, "columns");

    for (int i = 0; i < totaltiles; i ++) {
        all_tiles.push_back(
            TileEntry {
                sf::IntRect((i % columns) * tilesize.x, (i / columns) * tilesize.y,
                tilesize.x, tilesize.y),
                sf::IntRect()
            }
        );
    }

    rx::xml_node<> *image = node->first_node("image");
    img_src = attr<std::string>(image, "source");
    imagesize.x = attr<int>(image, "width");
    imagesize.y = attr<int>(image, "height");

    img_texture.loadFromFile("res/" + img_src);
    render_states.texture = &img_texture;

    rx::xml_node<> *tile_node = node->first_node();
    while (tile_node != nullptr) {
        std::string type = std::string(tile_node->name());
        if (type == "tile") {
            int indx = attr<int>(tile_node, "id");

            rx::xml_node<> *obj_group = tile_node->first_node("objectgroup");
            if (obj_group != nullptr) {
                rx::xml_node<> *obj = obj_group->first_node("object");
                if (obj != nullptr) {
                    all_tiles[indx].collision_rect = sf::IntRect(
                        attr<int>(obj, "x"), attr<int>(obj, "y"),
                        attr<int>(obj, "width"), attr<int>(obj, "height"));
                } else {
                    printf("TileSet '%s' has tile entry without object in object group\n", name.c_str());
                }
            }
        }
        tile_node = tile_node->next_sibling();
    }
}
const TileEntry& TileSet::getTile(const int gid)
{
    if ((size_t) gid > all_tiles.size()) {
        throw std::out_of_range(std::string("gid out of range: ") + std::to_string(gid));
    }
    return all_tiles.at(gid);
}
