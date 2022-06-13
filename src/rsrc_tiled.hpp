#ifndef RSRC_TILED_HPP
#define RSRC_TILED_HPP

#include "common.hpp"

void split(const std::string &s, char delim, std::vector<float> &result);
void split(const std::string &s, char delim, std::vector<int> &result);
void split(const std::string &s, char delim, std::vector<std::string> &result);

class TileMap;

class TileLayer
{
public:
    TileLayer(rx::xml_node<> *node);
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
    ObjectGroup(rx::xml_node<> *node);
    void build(TileMap* map);

    std::string name;
    int id;
    std::map<const int, sf::IntRect> objects;
};

struct TileSet {
    TileSet(rx::xml_node<> *node);

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
    rx::xml_document<>* doc;
};

/******************************************************************************/


struct TileEntry {
    const int gid;
    sf::IntRect texture_rect;
    std::vector<sf::IntRect> collision_rects;
};

struct FrameEntry {
    const int frame_gid;
    const int duration; // ms
};

class TileObject
{
public:
    TileObject(const char* filepath);
    ~TileObject();
    void build();

    rx::xml_document<>* doc;
    
    int firstgid, columns, totaltiles;
    sf::Vector2i tilesize, imagesize;
    sf::Texture img_texture;
    sf::RenderStates render_states;

    std::map<const int, TileEntry> tile_tbl;
    std::map<const std::string, std::vector<FrameEntry>> animation_rolls;

    std::string cfg_fp;
    int speed;
    int mass;
    int max_x_vel;
    int jump_power;
    float acl_gravity;
    float friction;
    float damping;
};


#endif // RSRC_TILED_HPP
