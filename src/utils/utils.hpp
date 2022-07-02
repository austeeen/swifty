#ifndef TLD_UTILS_HPP
#define TLD_UTILS_HPP

#include "../common.hpp"

namespace utl
{
    template<class T> inline void destroy(T*& p) { delete p; p = nullptr; }
    template<class T> inline void destroy(std::shared_ptr<T>& p) { p.reset(); }
    template<class K, class V> inline void destroy(std::map<K, V*>& tbl) {
        for (auto& [k, v] : tbl) { destroy(k); }
        tbl.clear();
    }
    template<class K, class V> inline void destroy(std::map<const K, V*>& tbl) {
        for (auto& [k, v] : tbl) { destroy(k); }
        tbl.clear();
    }

    void split(const std::string &s, char delim, std::vector<float> &result);
    void split(const std::string &s, char delim, std::vector<int> &result);
    void split(const std::string &s, char delim, std::vector<std::string> &result);


    bool stob(const std::string& str);
    sf::Vector2f stovf(const std::string& str);

    inline const float min(float a, float b) { return (a < b) ? a : b; };
    inline const float max(float a, float b) { return (a < b) ? b : a; };
}


#endif // TLD_UTILS_HPP
