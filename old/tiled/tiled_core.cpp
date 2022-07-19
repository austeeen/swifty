#include "tiled_core.hpp"

template <> bool attr(const rx::xml_node<> *n, const char *key)
{
    rx::xml_attribute<> *n_attr = n->first_attribute(key);
    if (n_attr == nullptr) {
        throw std::out_of_range(key);
    }
    return stob(std::string(n_attr->value()));
}
template<> bool attr_if(const rx::xml_node<> *n, const char* key)
{
    rx::xml_attribute<> *n_attr = n->first_attribute(key);
    if (n_attr == nullptr) {
        return false;
    }
    return stob(std::string(n_attr->value()));
}

namespace tld
{
Rect::Rect(rx::xml_node<>* node):
    id(attr<int>(node, "id")),
    x(attr<int>(node, "x")), y(attr<int>(node, "y")),
    w(attr<int>(node, "w")), h(attr<int>(node, "h")),
    gid(attr_if<int>(node, "gid")),
    name(attr_if<std::string>(node, "name")),
    type(attr_if<std::string>(node, "class"))
{}

void extractProperties(const rx::xml_node<> *prp, std::map<std::string, std::string>& prp_tbl)
{
    rx::xml_node<> *n = prp->first_node("property");
    while(n != nullptr) {
        std::string prp_name = attr<std::string>(n, "name");
        std::string prp_val = attr<std::string>(n, "value");
        prp_tbl[prp_name] = prp_val;
        n = n->next_sibling();
    }
}

void getRects(rx::xml_node<>* node, std::vector<Rect*>& rects)
{
    rx::xml_node<> *og = node->first_node("objectgroup");
    if (og) {
        rx::xml_node<> *obj = og->first_node("object");
        if (obj) {
            rects.push_back(new Rect(obj));
        }
    }
}
void getRects(rx::xml_node<>* node, std::map<const int, Rect*>& rects)
{
    rx::xml_node<> *og = node->first_node("objectgroup");
    if (og) {
        rx::xml_node<> *obj = og->first_node("object");
        if (obj) {
            rects[attr<int>(node, "id")] = new Rect(obj);
        }
    }
}
}
