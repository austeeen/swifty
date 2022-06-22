#ifndef TLD_TSX_HPP
#define TLD_TSX_HPP

#include "utils.hpp"

class TileMap;

/**************************************************************************************************/

class TsxBaseObject
{
public:
    std::string name;
    sf::Texture img_texture;
    sf::Vector2i tilesize;
};

/**************************************************************************************************/

struct ObjectEntry
{
    ObjectEntry(rx::xml_node<>* node);
    int id, gid;
    sf::FloatRect position_rect;
};

class DynamicTiledObject: public TsxBaseObject
{
public:
    DynamicTiledObject(rx::xml_node<>* node);
    void add(rx::xml_node<>* node);
    void combinePieces(TileMap *map);

    std::vector<ObjectEntry> pieces;
    std::string type;
    int speed;
    sf::Vector2f dest;
    bool horizontal;
    sf::FloatRect position_rect;
    sf::FloatRect collision_rect;
    CollisionRect collider;
    sf::VertexArray vertex_array;
    sf::RenderTexture* render_texture;
};

/**************************************************************************************************/

class TileObject: public TsxBaseObject
{
public:
    TileObject(const char* filepath);
    ~TileObject();
    void getProperties(rx::xml_node<>* node);
    void loadConfig(const char *cfg_fp);
    void addTile(rx::xml_node<>* node);
    void addRoll(std::shared_ptr<AnimRoll> roll, rx::xml_node<>* node);

    std::string img_src;
    int tilecount, columns, totaltiles;
    sf::Vector2i imagesize;
    sf::RenderStates render_states;
    std::map<const int, std::shared_ptr<TileFrame>> tile_tbl;
    std::map<ObjectState, std::shared_ptr<AnimRoll>> animation_rolls;
    std::string cfg_fp;
    PhysicsCoeffs pCoeffs;
};

#endif // TLD_TSX_HPP