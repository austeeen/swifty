#include "utils.hpp"

void loadXML(const char *fp, std::string &content, rx::xml_document<>* doc)
{
    std::ifstream file(fp);
    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();
    content = buffer.str();
    doc->parse<0>(&content[0]);
}

void split(const std::string &s, char delim, std::vector<float> &result)
{
    std::istringstream iss(s);
    for (std::string item; std::getline(iss, item, delim); )
        result.push_back(std::stof(item));
}
void split(const std::string &s, char delim, std::vector<int> &result)
{
    std::istringstream iss(s);
    for (std::string item; std::getline(iss, item, delim); )
        result.push_back(std::stoi(item));
}
void split(const std::string &s, char delim, std::vector<std::string> &result)
{
    std::istringstream iss(s);
    for (std::string item; std::getline(iss, item, delim); )
        result.push_back(item);
}
std::vector<float> split4(const std::string &s, char delim)
{
    std::vector<float> result;
    std::istringstream iss(s);
    for (std::string item; std::getline(iss, item, delim); )
        result.push_back(std::stoi(item));
    return result;
}
std::vector<float> split2(const std::string &s, char delim)
{
    std::vector<float> result;
    std::istringstream iss(s);
    for (std::string item; std::getline(iss, item, delim); )
        result.push_back(std::stoi(item));
    return result;
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

bool stob(const std::string& str)
{
    if(str == "false" || str == "False") {
        return false;
    } else if (str == "true" || str == "True") {
        return true;
    }
    throw std::invalid_argument(str);
}
sf::Vector2f stovf(const std::string& str)
{
    std::vector<std::string> rs;
    split(str, ',', rs);
    if (rs.size() != 2) {
        out::err("TileMap()", "%s != 2 int/float values", str);
        throw std::out_of_range(str);
    }
    return sf::Vector2f(std::stof(rs[0]), std::stof(rs[1]));
}

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
