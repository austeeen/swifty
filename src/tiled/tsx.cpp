#include "tsx.hpp"
#include "tmx.hpp"

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
