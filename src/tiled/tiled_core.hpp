#ifndef TLD_CORE_HPP
#define TLD_CORE_HPP

#include "../common.hpp"
#include "../utils/utils.hpp"
#include "../utils/rect.hpp"

template<class T> T attr(const rx::xml_node<> *n, const char* key)
{
    rx::xml_attribute<> *n_attr = n->first_attribute(key);
    T val;
    if (n_attr == nullptr) {
        throw std::out_of_range(key);
    }
    std::istringstream ss(n_attr->value());
    ss >> val;
    return val;
}
template<class T> T attr_if(const rx::xml_node<> *n, const char* key)
{
    rx::xml_attribute<> *n_attr = n->first_attribute(key);
    T val;
    if (n_attr == nullptr) {
        return val;
    }
    std::istringstream ss(n_attr->value());
    ss >> val;
    return val;
}

namespace tld
{
    struct Rect {
        Rect(rx::xml_node<>* node);
        const int id, x, y, w, h;
        int gid;
        std::string name, type;
    };

    void extractProperties(const rx::xml_node<> *prp, std::map<std::string, std::string>& prp_tbl);
    void getRects(rx::xml_node<>* node, std::vector<Rect*>& rects);
    void getRects(rx::xml_node<>* node, std::map<const int, Rect*>& rects);
}

#endif // TLD_CORE_HPP
