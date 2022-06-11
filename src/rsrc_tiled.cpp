#include "rsrc_tiled.hpp"

/******************************************************************************/

void openXmlFile(const char *filepath, rx::xml_document<>* doc)
{
  std::ifstream file(filepath);
  std::stringstream buffer;
  buffer << file.rdbuf();
  file.close();
  std::string content(buffer.str());
  doc->parse<0>(&content[0]);
}

void val(std::string& value, rx::xml_node<> *node)
{
  value = node->value();
}
void attr(int &dst, const char* attr_name, rx::xml_node<> *node)
{
  dst = std::atoi(node->first_attribute(attr_name)->value());
}
void attr(std::string &dst, const char* attr_name, rx::xml_node<> *node)
{
  dst = std::string(node->first_attribute(attr_name)->value());
}

/******************************************************************************/

void split(const std::string &s, char delim, std::vector<float> &result)
{
    std::istringstream iss(s);
    for (std::string item; std::getline(iss, item, delim); )
        result.push_back(std::stof(item));
}
void split(const std::string &s, char delim, std::vector<int> &result)
{
    std::istringstream iss(s);
    for (std::string item; std::getline(iss, item, delim); )
        result.push_back(std::stoi(item));
}
void split(const std::string &s, char delim, std::vector<std::string> &result)
{
    std::istringstream iss(s);
    for (std::string item; std::getline(iss, item, delim); )
        result.push_back(item);
}
std::vector<float> split4(const std::string &s, char delim)
{
    std::vector<float> result;
    std::istringstream iss(s);
    for (std::string item; std::getline(iss, item, delim); )
        result.push_back(std::stoi(item));
    return result;
}
std::vector<float> split2(const std::string &s, char delim)
{
    std::vector<float> result;
    std::istringstream iss(s);
    for (std::string item; std::getline(iss, item, delim); )
        result.push_back(std::stoi(item));
    return result;
}

/******************************************************************************/

LayerObject::LayerObject(rx::xml_node<> *node)
{
    attr(id, "id", node);
    attr(rect.left, "x", node);
    attr(rect.top, "y", node);
    attr(rect.width, "width", node);
    attr(rect.height, "height", node);
}

MapLayer::MapLayer(rx::xml_node<> *node)
{
    attr(name, "name", node);
    attr(id, "id", node);
}

TileLayer::TileLayer(rx::xml_node<> *node):
 MapLayer(node)
{
    attr(size.x, "width", node);
    attr(size.y, "height", node);
    rx::xml_node<> *data = node->first_node("data");
    val(gidstr, data);
}
void TileLayer::build(TileMap *map)
{
    render_texture.create(map->tilesize.x * size.x, map->tilesize.y * size.y);

    std::vector<int> all_gids = {};
    split(gidstr, ',', all_gids);
    vertices.setPrimitiveType(sf::Quads);
    vertices.resize(all_gids.size() * 4);

    TileSet *tile_set = nullptr;
    int tw = map->tilesize.x;
    int th = map->tilesize.y;
    int px, py, ix, iy;

    for (size_t i = 0; i < all_gids.size(); i++)
    {
        int gid = all_gids[i];
        px = (i % size.x) * tw;
        py = (i / size.x) * th;
        ix = (gid % size.x) * tw;
        iy = (gid / size.x) * th;

        sf::Vertex *quad = &vertices[i * 4];
        quad[0].position = sf::Vector2f(px,      py);
        quad[1].position = sf::Vector2f(px + tw, py);
        quad[2].position = sf::Vector2f(px + tw, py  + th);
        quad[3].position = sf::Vector2f(px,      py  + th);
        quad[0].texCoords = sf::Vector2f(ix,      iy);
        quad[1].texCoords = sf::Vector2f(ix + tw, iy);
        quad[2].texCoords = sf::Vector2f(ix + tw, iy  + th);
        quad[3].texCoords = sf::Vector2f(ix,      iy  + th);

        map->getTileset(gid, tile_set);
        sf::RenderStates rs(tile_set->img_texture);
        render_texture.draw(vertices[i], rs);
    }
}

ObjectGroup::ObjectGroup(rx::xml_node<> *node):
 MapLayer(node)
{
    rx::xml_node<> *obj_node = node->first_node();
    while (obj_node) {
      int id;
      attr(id, "id", obj_node);
      objects[id] = LayerObject(obj_node);
      obj_node = obj_node->next_sibling();
    }
}
void ObjectGroup::build(TileMap *map)
{

}

TileSet::TileSet(rx::xml_node<> *node)
{
    attr(name, "name", node);
    attr(firstgid, "firstgid", node);
    attr(tilesize.x, "tilewidth", node);
    attr(tilesize.y, "tileheight", node);
    attr(totaltiles, "tilecount", node);
    attr(columns, "columns", node);

    rx::xml_node<> *image = node->first_node("image");
    attr(img_src, "source", image);
    attr(imagesize.x, "width", image);
    attr(imagesize.y, "height", image);
    img_texture.loadFromFile(img_src);
}

TileMap::TileMap(const char* filepath)
{
  doc = new rx::xml_document<>();
  openXmlFile(filepath, doc);
  rx::xml_node<> *root = doc->first_node();
  rx::xml_node<> *map = root->first_node("map");
  attr(mapsize.x, "width", map);
  attr(mapsize.y, "height", map);
  attr(tilesize.x, "tilewidth", map);
  attr(tilesize.y, "tileheight", map);
  rx::xml_node<> *node = map->first_node();
  while (node) {
    std::string name;
    attr(name, "name", node);
    std::string type = std::string(node->name());
    if (type == "tileset") {
        int firstgid;
        attr(firstgid, "firstgid", node);
        tilesets[firstgid] = TileSet(node);
    }
    else if (type == "layer") {
      layers.push_back(TileLayer(node));
    }
    else if (type == "objectgroup") {
      layers.push_back(ObjectGroup(node));
    }
    node = node->next_sibling();
  }
}
void TileMap::build()
{
    for (auto& lyr : layers) {
        lyr.build(this);
    }
}
void TileMap::getTileset(const int cur_gid, TileSet *next_ts)
{
    for (auto itr = tilesets.end(); itr != tilesets.begin(); itr --) {
        next_ts = &itr->second;
        if (cur_gid < itr->first) {
            break;
        }
    }
}

/******************************************************************************/
