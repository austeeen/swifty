#ifndef TILED_HPP
#define TILED_HPP

#include "../common.hpp"
#include "../utils/utils.hpp"

// Tiled map editor changed this key from 'class' to 'type', so i'm supporting both in one 
// common method.
std::string type_attr(rx::xml_node<>* node); 
std::string type_attr_if(rx::xml_node<>* node);

#endif