#ifndef FCT_RSRCS_HPP
#define FCT_RSRCS_HPP

#include "common.hpp"

struct LayerObject {
  LayerObject(rx::xml_node<> *node);
  int id;
  sf::IntRect rect;
};

struct MapLayer {
  MapLayer(rx::xml_node<> *node);
  std::string name;
  int id;
};

struct TileLayer: MapLayer {
  TileLayer(rx::xml_node<> *node);
  std::string gid_str;
  sf::Vector2f size;
};

struct ObjectGroup: MapLayer {
  ObjectGroup(rx::xml_node<> *node);
  std::map<const int, LayerObject> objects;
};

struct TileSet {
  TileSet(rx::xml_node<> *node);
  std::string name, img_src;
  int first_gid, columns, total_tiles;
  sf::Vector2f tilesize, imagesize;
};


struct TileMap
{
  TileMap(const char* filepath);
  std::map<const std::string, TileSet> tilesets;
  std::map<const std::string, MapLayer> layers;
  sf::Vector2i mapsize, tilesize;
  rx::xml_document<>* doc;
};


#endif // FCT_RSRCS_HPP
