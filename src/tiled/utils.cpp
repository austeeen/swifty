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
        std::cout << str << " != 2 int/float values" << std::endl;
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

/**************************************************************************************************/

rect::rect():
    left(0.f), top(0.f), right(0.f), bottom(0.f), width(0.f), height(0.f)
{}
rect::rect(const float l, const float t, const float w, const float h):
    left(l), top(t), right(l + w), bottom(t + h), width(w), height(h)
{}
rect::rect(const sf::FloatRect& r):
    left(r.left), top(r.top), right(r.left + r.width), bottom(r.top + r.height), width(r.width), height(r.height)
{}
rect::rect(const rect& r):
    left(r.left), top(r.top), right(r.right), bottom(r.bottom), width(r.width), height(r.height)
{}
rect::operator sf::FloatRect() const
{
    return sf::FloatRect(left, top, width, height);
}
rect::operator bool() const
{
    return this->width != 0.f && this->height != 0.f;
}
const std::string rect::str() const
{
    std::stringstream ss;
    ss << (int) left << ", " << (int) top << ", " << (int) width << ", " << (int) height;
    return ss.str();
}
void rect::operator+=(const rect& r)
{
    this->left   = min(this->left,   r.left);
    this->top    = min(this->top,    r.top);
    this->right  = max(this->right,  r.right);
    this->bottom = max(this->bottom, r.bottom);
    this->width = this->right - this->left;
    this->height = this->bottom - this->top;
}
void rect::operator+=(const sf::FloatRect& r)
{
    *this += rect(r);
}
