#include "tileset.hpp"

Tile::Tile(const int gid, const int x, const int y):
    gid(gid), x(x), y(y)
{}
TileSet::TileSet(rx::xml_node<> *node):
    render_states(nullptr)
{
    name = attr<std::string>(node, "name");
    firstgid = attr<int>(node, "firstgid");
    tilesize.x = attr<int>(node, "tilewidth");
    tilesize.y = attr<int>(node, "tileheight");
    totaltiles = attr<int>(node, "tilecount");
    columns = attr<int>(node, "columns");

    rx::xml_node<> *image = node->first_node("image");
    img_src = attr<std::string>(image, "source");
    imagesize.x = attr<int>(image, "width");
    imagesize.y = attr<int>(image, "height");

    img_texture.loadFromFile("res/" + img_src);
    render_states = new sf::RenderStates(&img_texture);

    generateTiles();
    buildTiles(node);
    rx::xml_node<> *n = node->first_node("wangsets");
    if (n) {
        rx::xml_node<> *wnode = n->first_node("wangset");
        if (wnode) {
            setWangIndexes(wnode);
        }
    }
}
void TileSet::generateTiles()
{
    for (int i = 0; i < totaltiles; i ++) {
        Tile* t = new Tile(i, i % columns, i / columns);
        t->texture_rect = rect(
            (i % columns) * tilesize.x, (i / columns) * tilesize.y,
            tilesize.x, tilesize.y);
        all_tiles.push_back(t);
    }
}
void TileSet::buildTiles(rx::xml_node<>* node)
{
    for (rx::xml_node<> *tnode = node->first_node("tile"); tnode; tnode = tnode->next_sibling()) {
        if (std::string(tnode->name()) != "tile") {
            continue;
        }
        Tile* t = all_tiles[attr<int>(tnode, "id")];
        t->type = attr_if<std::string>(tnode, "class");
        tld::getRects(tnode, t->rects);
    }
}
void TileSet::setWangIndexes(rx::xml_node<> *node)
{
    for (rx::xml_node<> *wtile = node->first_node("wangtile"); wtile; wtile = wtile->next_sibling()) {
        if (std::string(wtile->name()) != "wangtile") {
            continue;
        }
        Tile* t = all_tiles[attr<int>(wtile, "tileid")];
        const char* wang_id = attr<std::string>(wtile, "wangid").c_str();
        for (int i = 0; i < 4; i ++) {
            if (wang_id[i * 4] == Wang::EDGE) {
                t->index |= 1 << i;
            }
        }
    }
}
Tile* TileSet::getTile(const int gid)
{
    if ((size_t) gid > all_tiles.size()) {
        throw std::out_of_range(std::string("gid out of range: ") + std::to_string(gid));
    }
    return all_tiles.at(gid);
}
const int TileSet::getFirstGid() const
{
    return this->firstgid;
}
sf::RenderStates* TileSet::getRenderStates() const
{
    return this->render_states;
}
