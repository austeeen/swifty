#ifndef UTIL_AABB_H
#define UTIL_AABB_H

#include "vec.hpp"

class AABB
{
public:
    typedef void(AABB::*moveFunc)(const float);

    struct val {
        val(AABB *r, const float v, moveFunc _mf);

        val& operator=(const val& v);
        val& operator=(const float v);
        val& operator+=(const val& dv);
        val& operator+=(const float dv);
        val& operator-=(const val& dv);
        val& operator-=(const float dv);

        operator bool() const;
        operator float() const;
        operator std::string() const;

    protected:
        friend class AABB;
        void move(const float d);
        void set(const float d);
    private:
        AABB *r;
        float mv;
        moveFunc mf;
    };

    struct vec {
        val x, y;

        vec(const val& x, const val& y);

        vec& operator=(const vec& v);
        template <class T>
        vec& operator=(const sf::Vector2<T>& v) {
            x = (float) v.x;
            y = (float) v.y;
            return *this;
        };

        vec& operator+=(const vec& v);
        template <class T>
        vec& operator+=(const sf::Vector2<T>& v) {
            x += (float) v.x;
            y += (float) v.y;
            return *this;
        };

        vec& operator-=(const vec& v);
        template <class T>
        vec& operator-=(const sf::Vector2<T>& v) {
            x -= (float) v.x;
            y -= (float) v.y;
            return *this;
        };

        operator bool() const;
        operator sf::Vector2f() const;
        operator std::string() const;
    };

    val left, right, top, bottom, width, height;
    vec center, pos;

    AABB();
    AABB(const AABB& r);
    AABB(const float x, const float y, const float w, const float h);
    AABB(const sf::FloatRect& fr);
    AABB(const sf::Vector2f &p, const sf::Vector2f &s);

    AABB& operator=(const AABB &r);

    void setPosition(const sf::Vector2f& p);
    void setPosition(const float x, const float y);

    void setSize(const sf::Vector2f& s);
    void setSize(const float x, const float y);

    void setCenter(const sf::Vector2f& c);
    void setCenter(const float x, const float y);

    sf::Vector2f getSize() const;
    sf::Vector2f getPosition() const;

    operator sf::FloatRect() const;
    operator std::string() const;
    operator bool() const;
    std::string tostr() const;

    static AABB clip(const AABB &a, const AABB &b);
    AABB clip(const AABB &other) const;

private:
    void __sl(const float dx) { right.move(dx);  center.x.move(dx); }
    void __sr(const float dx) { left.move(dx);   center.x.move(dx); }
    void __st(const float dy) { bottom.move(dy); center.y.move(dy); }
    void __sb(const float dy) { top.move(dy);    center.y.move(dy); }
    void __sw(const float dw) { right.move(dw);  center.x.move(dw / 2); }
    void __sh(const float dh) { bottom.move(dh); center.y.move(dh / 2); }
    void __scx(const float dx){ left.move(dx);     right.move(dx); }
    void __scy(const float dy){ top.move(dy);     bottom.move(dy); }
};

#endif // UTIL_AABB_H
