#include "locations_layer.hpp"
#include "tile_map.hpp"

Locations::Locations(rx::xml_node<>* node)
{
    name = attr<std::string>(node, "name");
    id = attr<int>(node, "id");
    rx::xml_node<> *obj_node = node->first_node();
    while (obj_node) {
        std::string type = attr<std::string>(obj_node, "type");
        if (type == "spawn") {
            std::string name = attr<std::string>(obj_node, "name");
            to_spawn[name] = sf::IntRect(
                attr<int>(obj_node, "x"), attr<int>(obj_node, "y"),
                attr<int>(obj_node, "width"), attr<int>(obj_node, "height")
            );
        }
        obj_node = obj_node->next_sibling();
    }
}

/**************************************************************************************************/

AiZones::AiZones(rx::xml_node<>* node)
{
    name = attr<std::string>(node, "name");
    id = attr<int>(node, "id");
    rx::xml_node<> *obj_node = node->first_node();
    while (obj_node) {
        std::string type = attr<std::string>(obj_node, "type");
        if (type == "zone") {
            std::string name = attr<std::string>(obj_node, "name");
            all_zones[name] = sf::IntRect(
                attr<int>(obj_node, "x"), attr<int>(obj_node, "y"),
                attr<int>(obj_node, "width"), attr<int>(obj_node, "height"));
        }
        obj_node = obj_node->next_sibling();
    }
}
