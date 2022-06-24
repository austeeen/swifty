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

inline const float min(float a, float b) { return (a < b) ? a : b; };
inline const float max(float a, float b) { return (a < b) ? b : a; };

struct rect {
    rect();
    rect(const float l, const float t, const float w, const float h);
    rect(const sf::FloatRect& r);
    rect(const rect& r);
    operator sf::FloatRect() const;
    operator bool() const;
    const std::string str() const;

    void operator+=(const rect& r);
    void operator+=(const sf::FloatRect& r);

    float left, top, right, bottom, width, height;
};

#endif // TLD_UTILS_HPP
