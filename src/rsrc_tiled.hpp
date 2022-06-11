#ifndef FCT_RSRCS_HPP
#define FCT_RSRCS_HPP

#include "common.hpp"

void split(const std::string &s, char delim, std::vector<float> &result);
void split(const std::string &s, char delim, std::vector<int> &result);
void split(const std::string &s, char delim, std::vector<std::string> &result);

struct TileMap;

struct LayerObject {
  LayerObject(rx::xml_node<> *node);

  int id;
  sf::IntRect rect;
};

struct MapLayer {
  MapLayer(rx::xml_node<> *node);
  virtual void build(TileMap* map) = 0;
  std::string name;
  int id;
};

struct TileLayer: MapLayer {
  TileLayer(rx::xml_node<> *node);
  void build(TileMap* map) override;
  std::string gidstr;
  sf::Vector2i size;
  sf::VertexArray vertices;
  sf::RenderTexture render_texture;
};

struct ObjectGroup: MapLayer {
  ObjectGroup(rx::xml_node<> *node);
  void build(TileMap* map) override;

  std::map<const int, LayerObject> objects;
};

struct TileSet {
  TileSet(rx::xml_node<> *node);

  sf::Texture img_texture;
  std::string name, img_src;
  int firstgid, columns, totaltiles;
  sf::Vector2i tilesize, imagesize;
};


struct TileMap {
  TileMap(const char* filepath);
  void build();
  void getTileset(const int cur_gid, TileSet *next_ts);
  std::map<const int, TileSet> tilesets;
  std::vector<MapLayer> layers;
  sf::Vector2i mapsize, tilesize;
  rx::xml_document<>* doc;
};


#endif // FCT_RSRCS_HPP
