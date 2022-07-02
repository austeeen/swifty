#include "tiled_core.hpp"

void loadXML(const char *fp, std::string &content, rx::xml_document<>* doc)
{
    std::ifstream file(fp);
    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();
    content = buffer.str();
    doc->parse<0>(&content[0]);
}
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
void extractProperties(const rx::xml_node<> *prp, PropertyTable& prp_tbl)
{
    rx::xml_node<> *n = prp->first_node("property");
    while(n != nullptr) {
        prp_tbl[attr<std::string>(n, "name")] = attr<std::string>(n, "value");
        n = n->next_sibling();
    }
}
