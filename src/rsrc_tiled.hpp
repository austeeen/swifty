#ifndef RSRC_TILED_HPP
#define RSRC_TILED_HPP

#include "common.hpp"

void split(const std::string &s, char delim, std::vector<float> &result);
void split(const std::string &s, char delim, std::vector<int> &result);
void split(const std::string &s, char delim, std::vector<std::string> &result);

template<class T> T attr(const rx::xml_node<> *n, const char* key)
{
    rx::xml_attribute<> *n_attr = n->first_attribute(key);
    T val;
    if (n_attr == nullptr) {
        throw std::out_of_range(key);
    }
    std::istringstream ss(n_attr->value());
    ss >> val;
    return val;
}
template<class T> T attr_if(const rx::xml_node<> *n, const char* key)
{
    rx::xml_attribute<> *n_attr = n->first_attribute(key);
    T val;
    if (n_attr == nullptr) {
        return val;
    }
    std::istringstream ss(n_attr->value());
    ss >> val;
    return val;
}

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

struct ObjectGroup {
    ObjectGroup(rx::xml_node<>* node);
    void build(TileMap* map);

    std::string name;
    int id;
    std::map<const int, sf::IntRect> objects;
};

struct TileSet {
    TileSet(rx::xml_node<>* node);

    std::string name, img_src;
    int firstgid, columns, totaltiles;
    sf::Vector2i tilesize, imagesize;
    sf::Texture img_texture;
    sf::RenderStates render_states;
};

class TileMap
{
public:
    TileMap(const char* filepath);
    ~TileMap();
    void build();
    TileSet* getTileset(const int cur_gid);

    std::map<const int, TileSet*> tilesets;
    std::vector<TileLayer*> tile_layers;
    std::vector<ObjectGroup*> object_groups;
    sf::Vector2i mapsize, tilesize;
};

/******************************************************************************/

class TileObject
{
public:
    TileObject(const char* filepath);
    ~TileObject();
    void getProperties(rx::xml_node<>* node);
    void loadConfig(const char *cfg_fp);
    void addTile(rx::xml_node<>* node);
    void addRoll(std::shared_ptr<AnimRoll> roll, rx::xml_node<>* node);

    std::string name, img_src;
    int tilecount, columns, totaltiles;
    sf::Vector2i tilesize, imagesize;
    sf::Texture img_texture;
    sf::RenderStates render_states;
    std::map<const int, std::shared_ptr<TileFrame>> tile_tbl;
    std::map<ObjectState, std::shared_ptr<AnimRoll>> animation_rolls;
    std::string cfg_fp;
    int speed;
    int mass;
    int max_x_vel;
    int jump_power;
    float acl_gravity;
    float damping;
};


#endif // RSRC_TILED_HPP
