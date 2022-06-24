#ifndef TLD_LAYERS_HPP
#define TLD_LAYERS_HPP

#include "utils.hpp"
#include "tsx.hpp"

class TileMap;


class TileLayer
{
public:
    TileLayer(rx::xml_node<>* node);
    ~TileLayer();
    void build(TileMap* map);

    std::string name;
    int id;
    std::string gidstr;
    sf::Vector2i size;
    sf::VertexArray vertex_array;
    sf::RenderTexture* render_texture;
};

/**************************************************************************************************/

struct ObjectGroup {
    ObjectGroup(rx::xml_node<>* node);
    void build(TileMap* map);

    std::string name;
    int id;
    std::vector<sf::IntRect> objects;
};

/**************************************************************************************************/

struct DynamicObjectGroup {
    DynamicObjectGroup(rx::xml_node<>* node);
    void build(TileMap* map);

    std::string name;
    int id;
    std::map<std::string, std::shared_ptr<DynamicTiledObject>> objects;
    std::map<int, sf::Vector2f> all_entries;
};


#endif // TLD_LAYERS_HPP
