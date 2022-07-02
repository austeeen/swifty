#include "tsx_object.hpp"

TsxObject::TsxObject(const char* filepath):
    doc(nullptr), content(nullptr)
{
    doc = new rx::xml_document<>();
    content = new std::string("");
    loadXML(filepath, *content, doc);
    if (!doc || !content) {
        printf("Error loading Tsx xml file: %s\n", filepath);
    }
}
void TsxObject::process()
{
    if (!doc || !content) {
        printf("Error processing Tsx file. File not loaded\n");
        return;
    }

    // get basic meta data
    rx::xml_node<> *ts_node = doc->first_node("tileset");
    name = attr<std::string>(ts_node, "name");
    tilesize.x = attr<int>(ts_node, "tilewidth");
    tilesize.y = attr<int>(ts_node, "tileheight");
    columns = attr<int>(ts_node, "columns");
    tilecount = attr<int>(ts_node, "tilecount");

    // will use to iterate over each node within this tileset
    rx::xml_node<> *node = ts_node->first_node();

    // valid node types: [image, properties, tile]
    std::string type;

    while(node) {
        type = std::string(node->name());
        if (type == "properties") {
            addProperties(node);
        } else if (type == "image") {
            setImage(node);
        } else if (type == "tile") {
            addTile(node);
        }
        node = node->next_sibling();
    }

    delete doc;
}
TsxObject::~TsxObject()
{
    utl::destroy(doc);
    utl::destroy(content);
    utl::destroy(tiles);
    utl::destroy(animations);

    prp_tbl.clear();
}
void TsxObject::addProperties(rx::xml_node<> *prp_node)
{
    extractProperties(prp_node, prp_tbl);

    // always assume a config entry exists (for now)
    std::string cfg_fp = "res/" + prp_tbl["config"];
    processConfig(cfg_fp.c_str());
}
void TsxObject::setImage(rx::xml_node<> *img_node)
{
    img.source = attr<std::string>(img_node, "source");
    img.size.x = attr<int>(img_node, "width");
    img.size.y = attr<int>(img_node, "height");
    img.texture.loadFromFile("res/" + img.source);
    img.render_states.texture = &img.texture;
}
void TsxObject::processConfig(const char *filepath)
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
    config.speed = attr<int>(phys, "speed");
    config.mass = attr<int>(phys, "mass");
    config.maxvel = attr<int>(phys, "maxvel");
    config.jump = attr<int>(phys, "jump");
    config.gravity = attr<int>(phys, "grav");
    config.damping = attr<int>(phys, "damping");
}
void TsxObject::addTile(rx::xml_node<> *node)
{
    Tile* tile = new Tile();
    const int gid = attr<int>(node, "id");
    tile->gid = gid;
    tile->type = attr_if<std::string>(node, "type");
    tile->texture_rect = sf::IntRect(
        (gid % columns) * tilesize.x,
        (gid / columns) * tilesize.y,
        tilesize.x,
        tilesize.y);

    // requiring every tile entry has an object group entry
    rx::xml_node<>* rect_entry = node->first_node("objectgroup")->first_node("object");
    while(rect_entry) {
        TileRect rect;
        rect.id = attr<int>(rect_entry, "id");
        rect.rect = sf::IntRect(
            attr<float>(rect_entry, "x"),
            attr<float>(rect_entry, "y"),
            attr<float>(rect_entry, "width"),
            attr<float>(rect_entry, "height")
        );
        rect.type = attr_if<std::string>(rect_entry, "type");
        rect_entry = rect_entry->next_sibling();
    }
    if (node->first_node("animation")) {
        addRoll(node);
    }
    tiles[gid] = tile;
}
void TsxObject::addRoll(rx::xml_node<> *tile_node)
{
    Roll* roll = new Roll();

    // requiring all animations have a type = to the parent tile's tile and properties located in
    // the parent tile
    roll->type = attr_if<std::string>(tile_node, "type");
    extractProperties(tile_node->first_node("properties"), roll->prps);

    rx::xml_node<> *frame_node = tile_node->first_node("animation")->first_node("frame");
    while(frame_node) {
        roll->frames.push_back(Frame {
            attr<int>(frame_node, "tileid"),
            attr<float>(frame_node, "duration") * 0.001f
        });
        frame_node = frame_node->next_sibling();
    }
    animations[roll->type] = roll;
}
