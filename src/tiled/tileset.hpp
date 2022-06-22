#ifndef TLD_TILESET_HPP
#define TLD_TILESET_HPP

#include "utils.hpp"

struct TileEntry {
    sf::IntRect texture_rect, collision_rect;
};

struct TileSet {
    TileSet(rx::xml_node<>* node);
    const TileEntry& getTile(const int gid);

    std::string name, img_src;
    int firstgid, columns, totaltiles;
    sf::Vector2i tilesize, imagesize;
    std::vector<TileEntry> all_tiles;
    sf::Texture img_texture;
    sf::RenderStates render_states;
};

#endif // TLD_TILESET_HPP
