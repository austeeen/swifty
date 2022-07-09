#ifndef TLD_TILESET_HPP
#define TLD_TILESET_HPP

#include "tiled_core.hpp"

namespace Wang {
    const char EDGE = '2';
    // EDGE: T = 1, R = 2, B = 4, L = 8
    const uint8_t TOP = 1;
    const uint8_t RIGHT = 2;
    const uint8_t BOT = 4;
    const uint8_t LEFT = 8;

    // index |= EDGE(true/false)
    typedef uint8_t Index; // bitmask

    enum class type {
        NONE = 0, B_CAP, L_CAP, BL_CRN,
        T_CAP, VERT, TL_CRN, R_INT,
        R_CAP, BR_CRN, HORZ, T_INT,
        TR_CRN, L_INT, B_INT, ALL_INT
    };
};

struct Tile {
    Tile(const int gid, const int x, const int y);
    const int gid, x, y;
    std::string type;
    rect texture_rect;
    std::vector<tld::Rect*> rects;
    Wang::Index index;
};

class TileSet
{
public:
    TileSet(rx::xml_node<>* node);
    Tile* getTile(const int gid);
    const int getFirstGid() const;
    sf::RenderStates* getRenderStates() const;

protected:
    void generateTiles();
    void buildTiles(rx::xml_node<>* node);
    void setWangIndexes(rx::xml_node<>* node);

private:
    std::string name, img_src;
    int firstgid, columns, totaltiles;
    sf::Vector2i tilesize, imagesize;
    std::vector<Tile*> all_tiles;
    sf::Texture img_texture;
    sf::RenderStates* render_states;
};

#endif // TLD_TILESET_HPP
