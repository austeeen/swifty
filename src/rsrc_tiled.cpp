#include "rsrc_tiled.hpp"

/******************************************************************************/

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
TileLayer::~TileLayer()
{
    delete render_texture;
    render_texture = nullptr;
}
void TileLayer::build(TileMap *map)
{
    render_texture->create(map->tilesize.x * size.x, map->tilesize.y * size.y);
    render_texture->clear(sf::Color::Transparent);

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

        render_texture->draw(quads, 4, sf::Quads, cur_tileset->render_states);
    }

    std::cout << "done building " << name << std::endl;
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

    rx::xml_node<> *image = node->first_node();
    attr(img_src, "source", image);
    attr(imagesize.x, "width", image);
    attr(imagesize.y, "height", image);

    img_texture.loadFromFile("res/" + img_src);
    render_states.texture = &img_texture;
}

TileMap::TileMap(const char* filepath)
{
    std::ifstream file(filepath);
    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();
    std::string content(buffer.str());

    doc = new rx::xml_document<>();
    doc->parse<0>(&content[0]);

    rx::xml_node<> *map = doc->first_node();
    attr(mapsize.x, "width", map);
    attr(mapsize.y, "height", map);
    attr(tilesize.x, "tilewidth", map);
    attr(tilesize.y, "tileheight", map);

    rx::xml_node<> *node = map->first_node();
    while(node != nullptr) {
        std::string type = std::string(node->name());
        printf("<%s ...> \n", type.c_str());
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
TileMap::~TileMap()
{
    for (auto& [gid, ts] : tilesets) {
        delete ts;
    }
    tilesets.clear();

    for (auto& tl : tile_layers) {
        delete tl;
    }
    tile_layers.clear();

    for (auto& og : object_groups) {
        delete og;
    }
    object_groups.clear();

    delete doc;
    doc = nullptr;
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
