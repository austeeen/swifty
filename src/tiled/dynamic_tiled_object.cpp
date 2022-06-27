#include "dynamic_tiled_object.hpp"
#include "tmx.hpp"

ObjectEntry::ObjectEntry(rx::xml_node<>* node)
{
    id = attr<int>(node, "id");
    gid = attr<int>(node, "gid");
    position_rect = rect(attr<int>(node, "x"), attr<int>(node, "y"),
                         attr<int>(node, "width"), attr<int>(node, "height"));
}

DynamicTiledObject::DynamicTiledObject(rx::xml_node<>* node):
    speed(-1), render_texture(new sf::RenderTexture()), type("")
{
    name = attr<std::string>(node, "name");
    type = attr<std::string>(node, "type");
}
DynamicTiledObject::~DynamicTiledObject()
{
    /*
    Waypoint* wp = root_waypoint;
    while (wp != nullptr) {
        Waypoint* nwp = wp->next;
        delete wp;
        wp = nwp;
    }
    root_waypoint = nullptr;
    */
}
void DynamicTiledObject::add(rx::xml_node<>* node)
{
    pieces.push_back(ObjectEntry(node));
    rx::xml_node<> *prps = node->first_node("properties");
    if (prps != nullptr) {
        std::map<std::string, std::string> prp_tbl;
        extractProperties(prps, prp_tbl);
        speed = std::stoi(prp_tbl.at("speed"));
        root_next_wp = std::stoi(prp_tbl.at("path"));
    }
}
void DynamicTiledObject::combinePieces(TileMap *map)
{
    // union all pieces' position_rects
    for (auto& obj : pieces) {
        if (! (bool) obj.position_rect) {
            continue;
        } else if (! (bool) position_rect) {
            position_rect = obj.position_rect;
            continue;
        } else {
            position_rect += obj.position_rect;
        }
    }

    // create the object's render texture similar to a tile layer
    render_texture->create(position_rect.width, position_rect.height);
    render_texture->clear(sf::Color::Transparent);
    vertex_array.resize(pieces.size() * 4);

    TileSet* cur_tileset;

    for (size_t i = 0; i < pieces.size(); ++i)
    {
        ObjectEntry& obj = pieces[i];

        int gid = obj.gid;
        if (gid == 0) {
            continue;
        }

        // normalized object's rect to position_rect's origin so we can position its texture
        const rect pos(
            obj.position_rect.left - position_rect.left,
            obj.position_rect.top - position_rect.top,
            obj.position_rect.width,
            obj.position_rect.height
        );

        sf::Vertex *quads = &vertex_array[i * 4];

        quads[0].position = sf::Vector2f(pos.left,  pos.top);
        quads[1].position = sf::Vector2f(pos.right, pos.top);
        quads[2].position = sf::Vector2f(pos.right, pos.bottom);
        quads[3].position = sf::Vector2f(pos.left,  pos.bottom);

        cur_tileset = map->getTileset(gid);
        int real_gid = gid - cur_tileset->firstgid;
        const TileEntry& tile = cur_tileset->getTile(real_gid);

        quads[0].texCoords = sf::Vector2f(tile.texture_rect.left, tile.texture_rect.top);
        quads[1].texCoords = sf::Vector2f(tile.texture_rect.right, tile.texture_rect.top);
        quads[2].texCoords = sf::Vector2f(tile.texture_rect.right, tile.texture_rect.bottom);
        quads[3].texCoords = sf::Vector2f(tile.texture_rect.left, tile.texture_rect.bottom);

        render_texture->draw(quads, 4, sf::Quads, cur_tileset->render_states);

        if ( !(bool)tile.collision_rect) {
            continue;
        }
        const rect col(
            pos.left + tile.collision_rect.left,
            pos.top + tile.collision_rect.top,
            tile.collision_rect.width,
            tile.collision_rect.height
        );
        if ( !(bool) collision_rect) {
            collision_rect = col;
        } else {
            collision_rect += col;
        }
    }
    render_texture->display();
    collider.offset = sf::Vector2f(collision_rect.left, collision_rect.top);
    collider.aabb = collision_rect;
    collider.type = ColliderType::platform;

    std::cout << "done building " << name << std::endl;
}
void DynamicTiledObject::setWaypointTree(std::map<int, Waypoint>& all_waypoints)
{
    // grab the waypoints, if any
    std::cout << name << std::endl;
    root_waypoint = new Waypoint(sf::Vector2f(position_rect.left, position_rect.top), root_next_wp);
    std::cout << " " << root_next_wp << std::endl;
    Waypoint* wp = root_waypoint->setNext(new Waypoint(all_waypoints[root_next_wp]));
    while(wp->next_id != -1) {
        std::cout << " " << wp->next_id << std::endl;
        wp = wp->setNext(new Waypoint(all_waypoints[wp->next_id]));
    }
    // wp->setNext(root_waypoint);
}
