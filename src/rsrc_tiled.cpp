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

TileLayer::TileLayer(rx::xml_node<> *node):
render_texture(new sf::RenderTexture())
{
    attr(name, "name", node);
    attr(id, "id", node);
    attr(size.x, "width", node);
    attr(size.y, "height", node);
    rx::xml_node<> *data = node->first_node("data");
    val(gidstr, data);
}
void TileLayer::build(TileMap *map)
{
    render_texture->create(map->tilesize.x * size.x, map->tilesize.y * size.y);
    render_texture->clear();

    std::vector<int> all_gids = {};
    split(gidstr, ',', all_gids);
    int tw = map->tilesize.x;
    int th = map->tilesize.y;
    int px, py, ix, iy;
    vertex_array.resize(size.x * size.y * 4);

    TileSet* cur_tileset;

    for (size_t i = 0; i < all_gids.size(); i++)
    {
        int gid = all_gids[i];
        if (gid == 0) {
            continue;
        }
        cur_tileset = map->getTileset(gid);
        int real_gid = gid - cur_tileset->firstgid;
        sf::RenderStates& rs = cur_tileset->render_states;
        std::cout << &rs << std::endl;

        // printf("%s - gid: %d | %s %d = %d\n", name.c_str(), gid, cur_tileset->name.c_str(), cur_tileset->firstgid, real_gid);

        /*
        sf::Vector2f pos((i % size.x) * tw, (i / size.x) * th);

        sf::IntRect texture_rect;
        texture_rect.left = (gid % cur_tileset->columns) * tw;
        texture_rect.top = (gid / cur_tileset->columns) * th;
        texture_rect.width = tw;
        texture_rect.height = th;

        sf::Sprite s(cur_tileset->img_texture, texture_rect);
        s.setPosition(pos);

        render_texture->draw(s);
        */
        px = (i % size.x) * tw;
        py = (i / size.x) * th;
        ix = (real_gid % cur_tileset->columns) * tw;
        iy = (real_gid / cur_tileset->columns) * th;

        sf::Vertex *quads = &vertex_array[i * 4];
        quads[0].position = sf::Vector2f(px,      py);
        quads[1].position = sf::Vector2f(px + tw, py);
        quads[2].position = sf::Vector2f(px + tw, py  + th);
        quads[3].position = sf::Vector2f(px,      py  + th);
        quads[0].texCoords = sf::Vector2f(ix,      iy);
        quads[1].texCoords = sf::Vector2f(ix + tw, iy);
        quads[2].texCoords = sf::Vector2f(ix + tw, iy  + th);
        quads[3].texCoords = sf::Vector2f(ix,      iy  + th);

        // printf("pos (%f, %f) | tex (%f, %f)\n", quads[0].position.x, quads[0].position.y, quads[0].texCoords.x, quads[0].texCoords.y);
        render_texture->draw(quads, 4, sf::Quads, rs);
    }
    render_texture->display();
}

ObjectGroup::ObjectGroup(rx::xml_node<> *node)
{
    attr(name, "name", node);
    attr(id, "id", node);
    rx::xml_node<> *obj_node = node->first_node();
    while (obj_node) {
      int id;
      attr(id, "id", obj_node);
      sf::IntRect rect;
      attr(rect.left, "x", obj_node);
      attr(rect.top, "y", obj_node);
      attr(rect.width, "width", obj_node);
      attr(rect.height, "height", obj_node);
      objects[id] = rect;
      obj_node = obj_node->next_sibling();
    }
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

    img_texture.loadFromFile("res/" + img_src);
    render_states.texture = &img_texture;
    std::cout << name << " " << &render_states << std::endl;
}

TileMap::TileMap(const char* filepath)
{
  doc = new rx::xml_document<>();
  openXmlFile(filepath, doc);
  rx::xml_node<> *map = doc->first_node("map");
  attr(mapsize.x, "width", map);
  attr(mapsize.y, "height", map);
  attr(tilesize.x, "tilewidth", map);
  attr(tilesize.y, "tileheight", map);

  rx::xml_node<> *node = map->first_node();
  while (node != NULL) {
    std::cout << node << std::endl;
    std::string type = std::string(node->name());
    // std::cout << "node: " << type << std::endl;
    if (type == "tileset") {
        int firstgid;
        attr(firstgid, "firstgid", node);
        tilesets[firstgid] = new TileSet(node);
    }
    else if (type == "layer") {
      tile_layers.push_back(new TileLayer(node));
    }
    else if (type == "objectgroup") {
      object_groups.push_back(new ObjectGroup(node));
    }
    node = node->next_sibling();
  }
}
void TileMap::build()
{
    for (auto& lyr : tile_layers) {
        std::cout << "building: " << lyr->name << std::endl;
        lyr->build(this);
    }
}
TileSet* TileMap::getTileset(const int cur_gid)
{
    int indx = 0; // arbitrary number
    for (auto [ts_gid, ts] : tilesets) {
        if (cur_gid >= ts_gid) {
            if (indx < ts_gid) {
                indx = ts_gid;
            }
        }
    }
    return tilesets[indx];
}

/******************************************************************************/
