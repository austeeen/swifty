#include "tile_layer.hpp"
#include "tile_map.hpp"

TileLayer::TileLayer(rx::xml_node<> *node):
    render_texture(new sf::RenderTexture())
{
    name = attr<std::string>(node, "name");
    id = attr<int>(node, "id");
    size.x = attr<int>(node, "width");
    size.y = attr<int>(node, "height");
    rx::xml_node<> *data = node->first_node("data");
    gidstr = data->value();
}
TileLayer::~TileLayer()
{
    delete render_texture;
    render_texture = nullptr;
}
void TileLayer::build(TileMap *map)
{
    render_texture->create(map->tilesize.x * size.x, map->tilesize.y * size.y);
    render_texture->clear(sf::Color::Transparent);

    std::vector<int> all_gids = {};
    split(gidstr, ',', all_gids);
    int tw = map->tilesize.x;
    int th = map->tilesize.y;
    int px, py;
    vertex_array.resize(size.x * size.y * 4);

    TileSet* cur_tileset;

    for (size_t i = 0; i < all_gids.size(); i++)
    {
        int gid = all_gids[i];
        if (gid == 0) {
            continue;
        }
        cur_tileset = map->getTileset(gid);
        const int real_gid = gid - cur_tileset->getFirstGid();
        px = (i % size.x) * tw;
        py = (i / size.x) * th;

        sf::Vertex *quads = &vertex_array[i * 4];
        quads[0].position = sf::Vector2f(px,      py);
        quads[1].position = sf::Vector2f(px + tw, py);
        quads[2].position = sf::Vector2f(px + tw, py  + th);
        quads[3].position = sf::Vector2f(px,      py  + th);

        Tile* mt = cur_tileset->getTile(real_gid);
        rect txt_rect = mt->texture_rect;

        quads[0].texCoords = sf::Vector2f(txt_rect.left, txt_rect.top);
        quads[1].texCoords = sf::Vector2f(txt_rect.left + txt_rect.width, txt_rect.top);
        quads[2].texCoords = sf::Vector2f(txt_rect.left + txt_rect.width,
                                          txt_rect.top  + txt_rect.height);
        quads[3].texCoords = sf::Vector2f(txt_rect.left, txt_rect.top  + txt_rect.height);

        render_texture->draw(quads, 4, sf::Quads, *cur_tileset->getRenderStates());
    }
    render_texture->display();
}
