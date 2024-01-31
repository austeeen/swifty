#include "tiled_core.hpp"

std::string type_attr(rx::xml_node<>* node)
{
    std::string type = attr_if<std::string>(node, "type");
    if (type.empty()) {
        type = attr<std::string>(node, "class");
    }
    return type;
}

std::string type_attr_if(rx::xml_node<>* node)
{
    std::string type = attr_if<std::string>(node, "type");
    if (type.empty()) {
        type = attr_if<std::string>(node, "class");
    }
    return type;
}