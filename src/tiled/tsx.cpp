#include "tsx.hpp"
#include "tmx.hpp"

ObjectEntry::ObjectEntry(rx::xml_node<>* node)
{
    id = attr<int>(node, "id");
    gid = attr<int>(node, "gid");
    position_rect = sf::FloatRect(
        attr<int>(node, "x"), attr<int>(node, "y"),
        attr<int>(node, "width"), attr<int>(node, "height"));
}

DynamicTiledObject::DynamicTiledObject(rx::xml_node<>* node):
    type(""),
    speed(-1),
    dest(0,0), horizontal(false),
    render_texture(nullptr)
{
    name = attr<std::string>(node, "name");
    type = attr<std::string>(node, "type");
}
void DynamicTiledObject::add(rx::xml_node<>* node)
{
    pieces.push_back(ObjectEntry(node));
    rx::xml_node<> *prps = node->first_node("properties");
    if (prps != nullptr) {
        std::map<std::string, std::string> prp_tbl;
        extractProperties(prps, prp_tbl);
        speed = std::stoi(prp_tbl.at("speed"));
        dest = stovf(prp_tbl.at("dest"));
        horizontal = stob(prp_tbl.at("horizontal"));
    }
}
void DynamicTiledObject::combinePieces(TileMap *map)
{
    const auto min = [](float a, float b) { return (a < b) ? a : b; };
    const auto max = [](float a, float b) { return (a < b) ? b : a; };

    // union all pieces' position_rects
    for (auto& obj : pieces) {
        if (position_rect.width == 0 && position_rect.height == 0) {
            position_rect = obj.position_rect;
            continue;
        }
        if (obj.position_rect.width == 0 && obj.position_rect.width == 0) {
            continue;
        }

        const float left   = min(position_rect.left, obj.position_rect.left);
        const float top    = min(position_rect.top,  obj.position_rect.top);
        const float right  = max(position_rect.left + position_rect.width,
                                 obj.position_rect.left + obj.position_rect.width);
        const float bottom = max(position_rect.top  + position_rect.height,
                                 obj.position_rect.top  + obj.position_rect.height);

        position_rect.left = left;
        position_rect.top = top;
        position_rect.width = right - position_rect.left;
        position_rect.height = bottom - position_rect.top;
    }

    // create the object's render texture similar to a tile layer
    render_texture->create(position_rect.width, position_rect.height);
    render_texture->clear(sf::Color::Transparent);

    // convert the destination from tile coordinates to pixel coordinates
    dest.x = map->tilesize.x * dest.x;
    dest.y = map->tilesize.y * dest.y;

    vertex_array.resize(position_rect.width * position_rect.height * 4);

    TileSet* cur_tileset;

    for (size_t i = 0; i < pieces.size(); ++i) {
        ObjectEntry& obj = pieces[i];
        int gid = obj.gid;
        if (gid == 0) {
            continue;
        }

        // normalized object's rect to position_rect's origin so we can position its texture
        sf::FloatRect p(
            obj.position_rect.left - position_rect.left,
            obj.position_rect.top - position_rect.top,
            obj.position_rect.width,
            obj.position_rect.height);

        sf::Vertex *quads = &vertex_array[i * 4];
        quads[0].position = sf::Vector2f(p.left, p.top);
        quads[1].position = sf::Vector2f(p.left + p.width, p.top);
        quads[2].position = sf::Vector2f(p.left + p.width, p.top  + p.height);
        quads[3].position = sf::Vector2f(p.left, p.top  + p.height);

        cur_tileset = map->getTileset(gid);
        int real_gid = gid - cur_tileset->firstgid;
        const TileEntry& tile = cur_tileset->getTile(real_gid);

        quads[0].texCoords = sf::Vector2f(tile.texture_rect.left, tile.texture_rect.top);
        quads[1].texCoords = sf::Vector2f(tile.texture_rect.left + tile.texture_rect.width, tile.texture_rect.top);
        quads[2].texCoords = sf::Vector2f(tile.texture_rect.left + tile.texture_rect.width,
                                          tile.texture_rect.top  + tile.texture_rect.height);
        quads[3].texCoords = sf::Vector2f(tile.texture_rect.left, tile.texture_rect.top  + tile.texture_rect.height);

        render_texture->draw(quads, 4, sf::Quads, cur_tileset->render_states);

        if (collision_rect.width == 0 && collision_rect.height == 0) {
            collision_rect = (sf::FloatRect) tile.collision_rect;
            continue;
        }
        if (tile.collision_rect.width == 0 && tile.collision_rect.width == 0) {
            continue;
        }

        const float left   = min(collision_rect.left, tile.collision_rect.left);
        const float top    = min(collision_rect.top,  tile.collision_rect.top);
        const float right  = max(collision_rect.left + collision_rect.width,
                                 tile.collision_rect.left + tile.collision_rect.width);
        const float bottom = max(collision_rect.top  + collision_rect.height,
                                 tile.collision_rect.top  + tile.collision_rect.height);

        collision_rect.left = left;
        collision_rect.top = top;
        collision_rect.width = right - collision_rect.left;
        collision_rect.height = bottom - collision_rect.top;
    }
    render_texture->display();

    collider.offset = sf::Vector2f(collision_rect.left, collision_rect.top);
    collider.aabb = collision_rect;
    collider.type = ColliderType::platform;

    std::cout << "done building " << name << std::endl;
}

/**************************************************************************************************/


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
    std::map<std::string, std::string> prop_tbl;
    extractProperties(all_properties, prop_tbl);

    std::string cfg_fp = prop_tbl["config"];
    cfg_fp = "res/" + cfg_fp;
    loadConfig(cfg_fp.c_str());
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
    pCoeffs.speed = attr<int>(phys, "speed");
    pCoeffs.mass = attr<int>(phys, "mass");
    pCoeffs.maxvel = attr<int>(phys, "maxvel");
    pCoeffs.jump = attr<int>(phys, "jump");
    pCoeffs.gravity = attr<int>(phys, "grav");
    pCoeffs.damping = attr<int>(phys, "damping");
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
        float col_x = std::round(attr<float>(c_rects, "x"));
        float col_y = std::round(attr<float>(c_rects, "y"));
        tile->collision_rects.push_back({
            sf::Vector2f(col_x, col_y),
            sf::FloatRect(col_x, col_y,
                std::round(attr<float>(c_rects, "width")), std::round(attr<float>(c_rects, "height"))),
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