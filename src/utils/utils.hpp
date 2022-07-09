#ifndef TLD_UTILS_HPP
#define TLD_UTILS_HPP

#include "../common.hpp"

void loadXML(const char *fp, std::string &content, rx::xml_document<>* doc);
void split(const std::string &s, char delim, std::vector<float> &result);
void split(const std::string &s, char delim, std::vector<int> &result);
void split(const std::string &s, char delim, std::vector<std::string> &result);

bool stob(const std::string& str);
sf::Vector2f stovf(const std::string& str);

inline const float min(float a, float b) { return (a < b) ? a : b; };
inline const float max(float a, float b) { return (a < b) ? b : a; };

#endif // TLD_UTILS_HPP
