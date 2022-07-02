#ifndef TLD_LAYERS_HPP
#define TLD_LAYERS_HPP

#include "tiled_core.hpp"

class TileMap;

/**************************************************************************************************/

class Layer
{
public:
    Layer(rx::xml_node<>* node);
    virtual void process(TileMap* map) =0;

    LayerType type;
    std::string name;
    int id;
};

/**************************************************************************************************/

class TileLayer: public Layer
{
public:
    TileLayer(rx::xml_node<>* node);
    void process(TileMap* map) override;

private:
    std::vector<int> gid_list;
    std::vector<Tile*> tiles;
    sf::Vector2i size;
    int numtiles;
};

/**************************************************************************************************/

class ObjectLayer: public Layer
{
public:
    ObjectLayer(rx::xml_node<>* node);
    void process(TileMap* map) override;

private:
    ObjectTable objtbl;
};




/*
class DynamicObjectAsset: public LayerObjectAsset
{
public:
    DynamicObjectAsset(rx::xml_node<>* node);
    ~DynamicObjectAsset();
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
    std::vector<LayerObjectAsset> pieces;
    std::string type;
    int root_next_wp;
    sf::VertexArray vertex_array;
};

struct SpawnLocations: public LayerBase
{
    SpawnLocations(rx::xml_node<>* node);

    std::map<std::string, sf::IntRect> to_spawn;
};


struct AiZones: public LayerBase
{
    AiZones(rx::xml_node<>* node);
    void build(TileMap* map);
    std::map<std::string, sf::IntRect> all_zones;
};
*/

#endif // TLD_LAYERS_HPP
