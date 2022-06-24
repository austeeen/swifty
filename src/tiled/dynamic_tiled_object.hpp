#ifndef TLD_DYNOBJ_HPP
#define TLD_DYNOBJ_HPP

#include "tsx.hpp"

struct ObjectEntry
{
    ObjectEntry(rx::xml_node<>* node);
    int id, gid;
    rect position_rect;
};

class DynamicTiledObject: public TsxBaseObject
{
public:
    DynamicTiledObject(rx::xml_node<>* node);
    ~DynamicTiledObject();
    void add(rx::xml_node<>* node);
    void combinePieces(TileMap *map);
    void setWaypointTree(std::map<int, Waypoint>& all_waypoints);

    int speed;
    Waypoint* root_waypoint;
    rect position_rect;
    CollisionRect collider;
    sf::RenderTexture* render_texture;

private:
    rect collision_rect;
    std::vector<ObjectEntry> pieces;
    std::string type;
    int root_next_wp;
    sf::VertexArray vertex_array;
};

#endif // TLD_DYNOBJ_HPP
