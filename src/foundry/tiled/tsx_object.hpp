#ifndef TSX_OBJECT_HPP
#define TSX_OBJECT_HPP

#include "tiled_core.hpp"

class TsxObject
{
public:
    TsxObject(const char* filepath);
    ~TsxObject();
    void process();

private:
    void addProperties(rx::xml_node<>* prp_node);
    void processConfig(const char *cfg_fp);
    void setImage(rx::xml_node<>* img_node);
    void addTile(rx::xml_node<>* tile_node);
    void addRoll(rx::xml_node<>* tile_node);

    rx::xml_document<>* doc;
    std::string* content;

    std::string name;
    sf::Vector2i tilesize;
    int tilecount, columns;
    Image img;
    Config config;
    PropertyTable prp_tbl;
    TileTable tiles;
    AnimationTable animations;
};



#endif // TSX_OBJECT_HPP
