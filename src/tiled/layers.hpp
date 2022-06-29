#ifndef TLD_LAYERS_HPP
#define TLD_LAYERS_HPP

#include "../utils/utils.hpp"
#include "dynamic_tiled_object.hpp"


struct LayerBase {
    LayerBase(rx::xml_node<>* node);
    std::string name;
    int id;
};

/**************************************************************************************************/

struct TileLayer: public LayerBase
{
    TileLayer(rx::xml_node<>* node);
    ~TileLayer();
    void build(TileMap* map);

    std::string gidstr;
    sf::Vector2i size;
    sf::VertexArray vertex_array;
    sf::RenderTexture* render_texture;
};

/**************************************************************************************************/

struct ObjectGroup: public LayerBase
{
    ObjectGroup(rx::xml_node<>* node);
    void build(TileMap* map);

    std::vector<sf::IntRect> objects;
};

/**************************************************************************************************/

struct DynamicObjectGroup: public LayerBase
{
    DynamicObjectGroup(rx::xml_node<>* node);
    void build(TileMap* map);

    std::map<std::string, std::shared_ptr<DynamicTiledObject>> objects;
    std::map<int, Waypoint> waypoints;
};

/**************************************************************************************************/

struct SpawnLocations: public LayerBase
{
    SpawnLocations(rx::xml_node<>* node);

    std::map<std::string, sf::IntRect> to_spawn;
};

/**************************************************************************************************/

struct AiPaths: public LayerBase
{
    AiPaths(rx::xml_node<>* node);
    void build(TileMap* map);
    std::map<std::string, std::vector<sf::IntRect>> all_paths;
};

#endif // TLD_LAYERS_HPP
