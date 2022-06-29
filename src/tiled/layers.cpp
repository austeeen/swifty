#include "layers.hpp"
#include "tmx.hpp"

LayerBase::LayerBase(rx::xml_node<> *node)
{
    name = attr<std::string>(node, "name");
    id = attr<int>(node, "id");
}

/**************************************************************************************************/

TileLayer::TileLayer(rx::xml_node<> *node):
    LayerBase(node), render_texture(new sf::RenderTexture())
{
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
        int real_gid = gid - cur_tileset->firstgid;
        px = (i % size.x) * tw;
        py = (i / size.x) * th;

        sf::Vertex *quads = &vertex_array[i * 4];
        quads[0].position = sf::Vector2f(px,      py);
        quads[1].position = sf::Vector2f(px + tw, py);
        quads[2].position = sf::Vector2f(px + tw, py  + th);
        quads[3].position = sf::Vector2f(px,      py  + th);

        const TileEntry& tile = cur_tileset->getTile(real_gid);
        quads[0].texCoords = sf::Vector2f(tile.texture_rect.left, tile.texture_rect.top);
        quads[1].texCoords = sf::Vector2f(tile.texture_rect.left + tile.texture_rect.width, tile.texture_rect.top);
        quads[2].texCoords = sf::Vector2f(tile.texture_rect.left + tile.texture_rect.width,
                                          tile.texture_rect.top  + tile.texture_rect.height);
        quads[3].texCoords = sf::Vector2f(tile.texture_rect.left, tile.texture_rect.top  + tile.texture_rect.height);

        render_texture->draw(quads, 4, sf::Quads, cur_tileset->render_states);
    }
    render_texture->display();
}

/**************************************************************************************************/

ObjectGroup::ObjectGroup(rx::xml_node<> *node):
    LayerBase(node)
{
    rx::xml_node<> *obj_node = node->first_node();
    while (obj_node) {
        objects.push_back(sf::IntRect(
            attr<int>(obj_node, "x"), attr<int>(obj_node, "y"),
            attr<int>(obj_node, "width"), attr<int>(obj_node, "height")
        ));
        obj_node = obj_node->next_sibling();
    }
}


/**************************************************************************************************/

DynamicObjectGroup::DynamicObjectGroup(rx::xml_node<> *node):
    LayerBase(node)
{
    rx::xml_node<> *obj_node = node->first_node();
    while (obj_node != nullptr) {

        int next_id = -1;
        rx::xml_node<> *prps = obj_node->first_node("properties");
        if (prps != nullptr) {
            std::map<std::string, std::string> prp_tbl;
            extractProperties(prps, prp_tbl);
            if (prp_tbl.count("next") != 0) {
                next_id = std::stoi(prp_tbl.at("next"));
            }
        }

        waypoints[attr<int>(obj_node, "id")] = Waypoint {
            sf::Vector2f(attr<int>(obj_node, "x"), attr<int>(obj_node, "y")), next_id
        };

        std::string type = attr_if<std::string>(obj_node, "type");
        if (type == "platform") {
            std::string obj_name = attr<std::string>(obj_node, "name");
            if (objects.count(obj_name) == 0) {
                objects[obj_name] = std::make_shared<DynamicTiledObject>(obj_node);
            }
            objects[obj_name]->add(obj_node);
        }
        obj_node = obj_node->next_sibling();
    }
}
void DynamicObjectGroup::build(TileMap *map)
{
    for (auto& [name, dyn_obj] : objects) {
        dyn_obj->combinePieces(map);
        dyn_obj->setWaypointTree(waypoints);
    }
}

/**************************************************************************************************/

SpawnLocations::SpawnLocations(rx::xml_node<>* node):
    LayerBase(node)
{
    rx::xml_node<> *obj_node = node->first_node();
    while (obj_node) {
        std::string type = attr<std::string>(obj_node, "type");
        if (type == "spawn") {
            std::string name = attr<std::string>(obj_node, "name");
            to_spawn[name] = sf::IntRect(
                attr<int>(obj_node, "x"), attr<int>(obj_node, "y"),
                attr<int>(obj_node, "width"), attr<int>(obj_node, "height")
            );
        }
        obj_node = obj_node->next_sibling();
    }
}

/**************************************************************************************************/

AiPaths::AiPaths(rx::xml_node<>* node):
    LayerBase(node)
{
    rx::xml_node<> *obj_node = node->first_node();
    while (obj_node) {
        std::string type = attr<std::string>(obj_node, "type");
        if (type == "waypoint") {
            std::string name = attr<std::string>(obj_node, "name");
            all_paths[name].push_back(sf::IntRect(
                attr<int>(obj_node, "x"), attr<int>(obj_node, "y"),
                attr<int>(obj_node, "width"), attr<int>(obj_node, "height")));
        }
        obj_node = obj_node->next_sibling();
    }
}
