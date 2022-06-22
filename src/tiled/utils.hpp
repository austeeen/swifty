#ifndef TLD_UTILS_HPP
#define TLD_UTILS_HPP

#include "../common.hpp"

void loadXML(const char *fp, std::string &content, rx::xml_document<>* doc);
void split(const std::string &s, char delim, std::vector<float> &result);
void split(const std::string &s, char delim, std::vector<int> &result);
void split(const std::string &s, char delim, std::vector<std::string> &result);

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

bool stob(const std::string& str);
sf::Vector2f stovf(const std::string& str);

void extractProperties(const rx::xml_node<> *prp, std::map<std::string, std::string>& prp_tbl);


#endif // TLD_UTILS_HPP
