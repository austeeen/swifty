#include "rsrc_tiled.hpp"


/******************************************************************************/

void loadXML(const char *fp, std::string &content, rx::xml_document<>* doc)
{
    std::ifstream file(fp);
    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();
    content = buffer.str();
    doc->parse<0>(&content[0]);
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

template <> bool attr(const rx::xml_node<> *n, const char *key)
{
    rx::xml_attribute<> *n_attr = n->first_attribute(key);
    if (n_attr == nullptr) {
        throw std::out_of_range(key);
    }
    char *c_attr = n_attr->value();
    if(std::string(c_attr) == "false") {
        return false;
    } else if (std::string(c_attr) == "true") {
        return true;
    }
    throw std::invalid_argument(key);
}
template<> bool attr_if(const rx::xml_node<> *n, const char* key)
{
    rx::xml_attribute<> *n_attr = n->first_attribute(key);
    if (n_attr == nullptr) {
        return false;
    }
    char *c_attr = n_attr->value();
    if(std::string(c_attr) == "false") {
        return false;
    } else if (std::string(c_attr) == "true") {
        return true;
    }
    throw std::invalid_argument(key);
}

/******************************************************************************/

TileLayer::TileLayer(rx::xml_node<> *node):
render_texture(new sf::RenderTexture())
{
    name = attr<std::string>(node, "name");
    id = attr<int>(node, "id");
    size.x = attr<int>(node, "width");
    size.y = attr<int>(node, "height");
    rx::xml_node<> *data = node->first_node("data");
    gidstr = data->value();
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
    name = attr<std::string>(node, "name");
    id = attr<int>(node, "id");

    rx::xml_node<> *obj_node = node->first_node();
    while (obj_node) {
        int obj_id = attr<int>(obj_node, "id");
        sf::IntRect rect;
        rect.left = attr<int>(obj_node, "x");
        rect.top = attr<int>(obj_node, "y");
        rect.width = attr<int>(obj_node, "width");
        rect.height = attr<int>(obj_node, "height");
        objects[obj_id] = rect;
        obj_node = obj_node->next_sibling();
    }
}

TileSet::TileSet(rx::xml_node<> *node)
{
    name = attr<std::string>(node, "name");
    firstgid = attr<int>(node, "firstgid");
    tilesize.x = attr<int>(node, "tilewidth");
    tilesize.y = attr<int>(node, "tileheight");
    totaltiles = attr<int>(node, "tilecount");
    columns = attr<int>(node, "columns");

    rx::xml_node<> *image = node->first_node();
    img_src = attr<std::string>(image, "source");
    imagesize.x = attr<int>(image, "width");
    imagesize.y = attr<int>(image, "height");

    img_texture.loadFromFile("res/" + img_src);
    render_states.texture = &img_texture;
}

TileMap::TileMap(const char* filepath)
{
    rx::xml_document<>* doc = new rx::xml_document<>();
    std::string content = "";
    loadXML(filepath, content, doc);
    if (doc == nullptr || content == "") {
        std::cout << "tile map construction failed" << std::endl;
        return;
    }
    rx::xml_node<> *map = doc->first_node();
    mapsize.x = attr<int>(map, "width");
    mapsize.y = attr<int>(map, "height");
    tilesize.x = attr<int>(map, "tilewidth");
    tilesize.y = attr<int>(map, "tileheight");
    rx::xml_node<> *node = map->first_node();
    while(node != nullptr) {
        std::string type = std::string(node->name());
        printf("<%s ...> \n", type.c_str());
        if (type == "tileset") {
            int firstgid = attr<int>(node, "firstgid");
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
    delete doc;
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
}
void TileMap::build()
{
    for (auto& lyr : tile_layers) {
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

TileObject::TileObject(const char* filepath)
{
    rx::xml_document<>* doc = new rx::xml_document<>();
    std::string content = "";
    loadXML(filepath, content, doc);
    if (doc == nullptr || content == "") {
        std::cout << "tile object construction failed" << std::endl;
        return;
    }

    rx::xml_node<> *ts_node = doc->first_node("tileset");
    name = attr<std::string>(ts_node, "name");
    tilesize.x = attr<int>(ts_node, "tilewidth");
    tilesize.y = attr<int>(ts_node, "tileheight");
    columns = attr<int>(ts_node, "columns");
    totaltiles = attr<int>(ts_node, "tilecount");

    std::string type;
    rx::xml_node<> *node = ts_node->first_node();
    while(node != nullptr) {
        type = std::string(node->name());
        if (type == "properties") {
            getProperties(node);
        } else if (type == "image") {
            img_src = attr<std::string>(node, "source");
            imagesize.x = attr<int>(node, "width");
            imagesize.y = attr<int>(node, "height");
            img_texture.loadFromFile("res/" + img_src);
        } else if (type == "tile") {
            addTile(node);
        }
        node = node->next_sibling();
    }

    node = ts_node->first_node();
    while(node != nullptr) {
        std::string anim_roll = attr_if<std::string>(node, "type");
        if (anim_roll == "idle") {
            addRoll(animation_rolls[ObjectState::idle], node);
        } else if (anim_roll == "running") {
            addRoll(animation_rolls[ObjectState::running], node);
        } else if (anim_roll == "jumping") {
            addRoll(animation_rolls[ObjectState::jumping], node);
        } else if (anim_roll == "falling") {
            addRoll(animation_rolls[ObjectState::falling], node);
        }
        node = node->next_sibling();
    }

    delete doc;
}
TileObject::~TileObject()
{
    tile_tbl.clear();
    animation_rolls.clear();
}
void TileObject::getProperties(rx::xml_node<> *all_properties)
{
    std::string prp_type, prp_name;
    rx::xml_node<> *prp = all_properties->first_node("property");
    while(prp != nullptr) {
        prp_type = attr<std::string>(prp, "type");
        prp_name = attr<std::string>(prp, "name");
        if (prp_name == "config") {
            if (prp_type == "file") {
                std::string cfg_fp = attr<std::string>(prp, "value");
                loadConfig(cfg_fp.c_str());
            }
        }
        prp = prp->next_sibling();
    }
}
void TileObject::loadConfig(const char *filepath)
{
    rx::xml_document<>* doc = new rx::xml_document<>();
    std::string content = "";
    loadXML(filepath, content, doc);
    if (doc == nullptr || content == "") {
        std::cout << "tile object config construction failed" << std::endl;
        return;
    }
    rx::xml_node<> *cfg = doc->first_node("config");
    rx::xml_node<> *phys = cfg->first_node("physics");
    speed = attr<int>(phys, "speed");
    mass = attr<int>(phys, "mass");
    max_x_vel = attr<int>(phys, "maxvel");
    jump_power = attr<int>(phys, "jump");
    acl_gravity = attr<int>(phys, "grav");
    damping = attr<int>(phys, "damping");
}
void TileObject::addTile(rx::xml_node<> *node)
{
    std::shared_ptr<TileFrame> tile = std::make_shared<TileFrame>();
    tile->duration = 0.f;
    int gid = attr<int>(node, "id");
    tile->gid = gid;
    tile->texture_rect = sf::IntRect((gid % columns) * tilesize.x, (gid / columns) * tilesize.y,
                                    tilesize.x, tilesize.y);
    rx::xml_node<>* c_rects = node->first_node("objectgroup")->first_node("object");
    while(c_rects != nullptr) {
        std::string type = attr_if<std::string>(c_rects, "type");
        ColliderType ct = ColliderType::generic;
        if (type == "body") {
            ct = ColliderType::body;
        }
        float col_x = attr<int>(c_rects, "x");
        float col_y = attr<int>(c_rects, "y");
        float col_w = attr<int>(c_rects, "width");
        float col_h = attr<int>(c_rects, "height");
        tile->collision_rects.push_back({
            sf::Vector2f(col_x, col_y),
            sf::FloatRect(col_x, col_y, col_w, col_h),
            ct
        });
        c_rects = c_rects->next_sibling();
    }
    tile_tbl[gid] = tile;

    std::string anim_roll = attr_if<std::string>(node, "type");
    if (anim_roll == "idle") {
        animation_rolls[ObjectState::idle] = std::make_shared<AnimRoll>();
    } else if (anim_roll == "running") {
        animation_rolls[ObjectState::running] = std::make_shared<AnimRoll>();
    } else if (anim_roll == "jumping") {
        animation_rolls[ObjectState::jumping] = std::make_shared<AnimRoll>();
    } else if (anim_roll == "falling") {
        animation_rolls[ObjectState::falling] = std::make_shared<AnimRoll>();
    }
}
void TileObject::addRoll(std::shared_ptr<AnimRoll> roll, rx::xml_node<> *node)
{
    rx::xml_node<> *prp = node->first_node("properties")->first_node("property");
    while(prp != nullptr) {
        std::string prp_name = attr<std::string>(prp, "name");
        if (prp_name == "end_early") {
            roll->end_early_frame = attr_if<int>(prp, "value");
        } else if (prp_name == "hold_last") {
            roll->hold_last_frame = attr_if<bool>(prp, "value");
        } else if (prp_name == "one_shot") {
            roll->one_shot = attr_if<bool>(prp, "value");
        }
        prp = prp->next_sibling();
    }

    rx::xml_node<> *frame_entry = node->first_node("animation")->first_node("frame");
    while(frame_entry != nullptr) {
        int gid = attr<int>(frame_entry, "tileid");
        std::shared_ptr<TileFrame> frame = tile_tbl[gid];
        frame->duration = attr<float>(frame_entry, "duration") * 0.001f;
        roll->frames.push_back(frame);
        frame_entry = frame_entry->next_sibling();
    }
}
