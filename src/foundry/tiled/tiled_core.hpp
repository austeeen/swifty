#ifndef TILED_CORE_HPP
#define TILED_CORE_HPP

#include "../foundry_core.hpp"

void loadXML(const char *fp, std::string &content, rx::xml_document<>* doc);

/**************************************************************************************************/

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

/**************************************************************************************************/

typedef std::map<const std::string, std::string> PropertyTable;

void extractProperties(const rx::xml_node<> *prp, PropertyTable& prp_tbl);

/**************************************************************************************************/

struct Image
{
    std::string source;
    sf::Vector2i size;
    sf::Texture texture;
    sf::RenderStates render_states;
};

/**************************************************************************************************/

struct TileRect {
    int id;
    std::string type;
    sf::IntRect rect;
};

struct Tile {
    int gid;
    std::string type;
    sf::Vertex quads[4];
    std::vector<TileRect> rects;
    PropertyTable prps;
    sf::RenderStates render_states;
};
typedef std::map<const int, Tile*> TileTable;

/**************************************************************************************************/

struct Frame {
    const int gid;
    const float dur;
};

struct Roll {
    std::string type;
    PropertyTable prps;
    std::vector<Frame> frames;
};
typedef std::map<const std::string, Roll*> AnimationTable;

/**************************************************************************************************/

struct Config {
    int mass, speed, maxvel, jump, gravity, damping;
};

/**************************************************************************************************/

struct TiledObject
{
    int id, gid;
    std::string name, type;
    sf::IntRect rect;
    PropertyTable prps;
};
typedef std::map<const int, TiledObject*> ObjectTable;
/**************************************************************************************************/

#endif // TILED_CORE_HPP
