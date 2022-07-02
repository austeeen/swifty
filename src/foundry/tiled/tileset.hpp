#ifndef TLD_TILESET_HPP
#define TLD_TILESET_HPP

#include "tiled_core.hpp"

class TileSet
{
public:
    TileSet(rx::xml_node<>* node);
    ~TileSet();

    const Tile& getTile(const int gid) const;
    const int getFirstGid() const;
    const sf::RenderStates getRenderStates() const;

private:
    void setImage(rx::xml_node<>* node);
    void updateTile(rx::xml_node<>* node);

    std::string name;
    int firstgid, columns, totaltiles;
    sf::Vector2i tilesize;
    TileTable tiles;
    Image img;
};

#endif // TLD_TILESET_HPP
