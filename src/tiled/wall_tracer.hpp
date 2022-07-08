#ifndef TLD_WALLTRACER_HPP
#define TLD_WALLTRACER_HPP

#include "../common.hpp"
#include "../utils/utils.hpp"

/*
    implements an agent to 'trace' over a tile layer, merging adjacent tiles' collision rects, to
    create the smallest number of collision rects possible for a single layer

    ╔═╗
    ║ ║     = 4 rects
    ╚═╝

    ╔══╗
    ╠══╣    = 5 rects
    ╚══╝

     ║
    ═╬═     = 2 rects
     ║

     ╦═
     ║      = 3 rects
    ═╩


*/

enum class DIR4 { UP, DOWN, LEFT, RIGHT };

const char HASEDGE = '2';


namespace Wangset {
    enum class type {
        NONE = 0, B_CAP, L_CAP, BL_CRN,
        T_CAP, VERT, TL_CRN, R_INT,
        R_CAP, BR_CRN, HORZ, T_INT,
        TR_CRN, L_INT, B_INT, ALL_INT
    };
};

enum class TerrainType { boundary, webbed };

struct Tile
{
    Tile(const int gid, const int x, const int y):
        adj{nullptr, nullptr, nullptr, nullptr},
        gid(gid), x(x), y(y)
    {};
    const int gid, x, y;
    sf::IntRect position;
    std::vector<sf::IntRect> origin_rects, normed_rects;
    TerrainType trn;
    Wangset::type type;

    void setNeighbor(DIR4 d, Tile* t);
    bool hasNeighbor(DIR4 d);
    Tile* getNeighbor(DIR4 d);
    void clearNeighbor(DIR4 dir);

private:
    Tile* adj[4];
};

struct RectStructure
{
    std::vector<Tile*> subtiles;
    sf::IntRect merged_rect;
    TerrainType inferred_terrain;
};

class Tracer
{
public:
    Tracer(rx::xml_node<>* node);
    void traceGidStr(const std::string& gid_str, const sf::Vector2i& size);


    std::map<int, int> wangset;
    std::vector<RectStructure> combined_rects;
};


#endif // TLD_WALLTRACER_HPP
