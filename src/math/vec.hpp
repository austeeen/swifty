#ifndef UTIL_MATH_H
#define UTIL_MATH_H

#include <sstream>
#include <SFML/Graphics.hpp>

struct vec
{
    float x, y;

    vec(): x(0.f), y(0.f) {};
    vec(float x, float y): x(x), y(y) {};
    vec(int x, int y): x(x), y(y) {};

    vec& operator=(const vec& v) {
        this->x = v.x; this->y = v.y; return *this;
    };
    template <class T> vec& operator=(const sf::Vector2<T>& v) {
        this->x = (float) v.x; this->y = (float) v.y; return *this;
    };

    operator bool() const {
        return (x != 0 && y != 0);
    };
    template <class T> operator sf::Vector2<T>() const {
        return sf::Vector2<T>(x, y);
    };

    const float operator[](const int i) const {
        return (i % 2 == 0) ? x : y;
    };

    friend std::ostream &operator<<(std::ostream &output, const vec &v) {
        output << "(" << v.x << ", " << v.y << + ")";
        return output;
    }
    const std::string tostr() const {
        std::stringstream ss;
        ss << this;
        return ss.str();
    };
};

#endif // UTIL_MATH_H
