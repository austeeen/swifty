#ifndef TLD_MAP_HPP
#define TLD_MAP_HPP

#include "layers.hpp"
#include "tileset.hpp"

class Foundry;

class TileMap
{
public:
    TileMap(const char* filepath);
    ~TileMap();
    void process();
    TileSet* getTileset(const int cur_gid);
    sf::Vector2i getTileSize() const;

    std::string name;
    sf::Vector2i mapsize, tilesize;
    std::map<const int, TileSet*> tilesets;
    std::map<const std::string, TileLayer*> tilelayers;
    std::map<const std::string, ObjectLayer*> objectlayers;

private:
    rx::xml_document<>* doc;
    std::string* content;
};

#endif // TLD_MAP_HPP
