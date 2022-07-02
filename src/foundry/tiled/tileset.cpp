#include "tileset.hpp"

TileSet::TileSet(rx::xml_node<> *node)
{
    name = attr<std::string>(node, "name");
    firstgid = attr<int>(node, "firstgid");
    tilesize.x = attr<int>(node, "tilewidth");
    tilesize.y = attr<int>(node, "tileheight");
    totaltiles = attr<int>(node, "tilecount");
    columns = attr<int>(node, "columns");

    for (int i = 0; i < totaltiles; i ++)
    {
        Tile* t = new Tile();
        t->gid = i;
        const int tw = tilesize.x;
        const int th = tilesize.y;
        const int tx = (i % columns) * tw;
        const int ty = (i / columns) * th;
        t->quads[0].texCoords = sf::Vector2f(tx, ty);
        t->quads[1].texCoords = sf::Vector2f(tx + tw, ty);
        t->quads[2].texCoords = sf::Vector2f(tx + tw, ty + th);
        t->quads[3].texCoords = sf::Vector2f(tx, ty + th);
        tiles[i] = t;
    }

    setImage(node->first_node("image"));

    for (rx::xml_node<> *tnode = node->first_node(); tnode != nullptr; tnode = tnode->next_sibling())
    {
        if (std::string(tnode->name()) == "tile") {
            updateTile(tnode);
        }
    }
}
TileSet::~TileSet()
{
    utl::destroy(tiles);
}
const Tile& TileSet::getTile(const int gid) const
{
    return *tiles.at(gid);
}
const int TileSet::getFirstGid() const
{
    return firstgid;
}
const sf::RenderStates TileSet::getRenderStates() const
{
    return img.render_states;
}
void TileSet::setImage(rx::xml_node<> *img_node)
{
    img.source = attr<std::string>(img_node, "source");
    img.size.x = attr<int>(img_node, "width");
    img.size.y = attr<int>(img_node, "height");
    img.texture.loadFromFile("res/" + img.source);
    img.render_states.texture = &img.texture;
}
void TileSet::updateTile(rx::xml_node<> *node)
{
    const int id = attr<int>(node, "id");
    tiles[id]->type = attr_if<std::string>(node, "type");
    rx::xml_node<> *group = node->first_node("objectgroup");
    if (group)
    {
        for (rx::xml_node<> *obj = group->first_node(); obj != nullptr; obj = obj->next_sibling())
        {
            TileRect r;
            r.id = attr<int>(obj, "id");
            r.type = attr_if<int>(obj, "type");
            r.rect = sf::IntRect(
                attr<int>(obj, "x"),
                attr<int>(obj, "y"),
                attr<int>(obj, "width"),
                attr<int>(obj, "height"));
            tiles[id]->rects.push_back(r);
        }
    }
}
