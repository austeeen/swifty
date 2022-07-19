#ifndef TLD_STRUCTURE_LAYERS_HPP
#define TLD_STRUCTURE_LAYERS_HPP

#include "tiled_core.hpp"

class TileMap;

class StructureLayer
{
public:
    StructureLayer(rx::xml_node<>* node);
    virtual ~StructureLayer();
    virtual void build(TileMap *map) = 0;

protected:
    std::string name;
    int id;
};

/**************************************************************************************************/

class StaticStructures: public StructureLayer
{
public:
    StaticStructures(rx::xml_node<>* node);
    ~StaticStructures();
    void build(TileMap* map) override;

private:
    std::vector<tld::Rect*> all_rects;
    std::vector<sf::IntRect> objects;
};

/**************************************************************************************************/

class DynamicStructures: public StructureLayer
{
public:
    DynamicStructures(rx::xml_node<>* node);
    ~DynamicStructures();
    void build(TileMap* map) override;

private:
    std::map<const int, tld::Rect*> objects;
    std::map<int, Waypoint> waypoints;
};

/**************************************************************************************************/

class TerrainStructures: public StructureLayer
{
public:
    TerrainStructures(rx::xml_node<>* node);
    ~TerrainStructures();
    void build(TileMap* map) override;

private:
    std::map<const int, tld::Rect*> objects;
};

#endif // TLD_STRUCTURE_LAYERS_HPP
