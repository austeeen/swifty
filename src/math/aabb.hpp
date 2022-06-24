#ifndef UTIL_AABB_H
#define UTIL_AABB_H

#include <SFML/Graphics.hpp>

/*
class rect
{
public:

    struct val
    {
    private:
        rect *r;
        float mv;
        void(rect::*__move)(const float);
    public:
        val(rect *r, const float v, void(rect::*_m)(const float));
        val& operator=(const val& v);
        val& operator=(const float v);
        val& operator+=(const float dv);
        val& operator-=(const float dv);
        operator float() const;
        std::string tostr() const;
        void move(const float d);
        void set(const float d);
    };

    struct point
    {
    private:
        val* xy[2];
        val *x, *y;
    public:
        point(val *x, val *y);
        point& operator=(const point& v);
        template <class ITGR>
        point& operator=(const sf::Vector2<ITGR>& v) {
            *x = (float) v.x;
            *y = (float) v.y;
            return *this;
        };

        operator sf::Vector2f() const;
        std::string tostr() const;
        val& operator[](const int i) const;
    };

    val left, right, top, bottom, centerx, centery, width, height;
    point center, pos, size;

    rect();
    rect(const float x, const float y, const float w, const float h);
    rect(const sf::FloatRect& fr);
    rect(const sf::Vector2f &p, const sf::Vector2f &s);
    rect(const std::vector<float> &v);
    rect(const rect& r);

    rect& operator=(const rect &r);

    inline void move(float x, float y) {
        this->left += x;
        this->top  += y;
    }

    inline void shrink(int s) {
        this->width -= s;
        this->height -= s;
    }

    void setPosition(const sf::Vector2f& p);
    void setPosition(const float x, const float y);

    void setSize(const sf::Vector2f& s);
    void setSize(const float x, const float y);

    void setCenter(const sf::Vector2f& c);
    void setCenter(const float x, const float y);

    sf::Vector2f getSize() const;
    sf::Vector2f getPosition() const;

    operator sf::FloatRect() const;
    operator sf::IntRect() const;

    std::string tostr() const;

    static rect clip(const rect &a, const rect &b);
    rect clip(const rect &rect) const;

    const bool exists() const;

private:
    void __sl(const float dx) { right.move(dx);  centerx.move(dx); }
    void __sr(const float dx) { left.move(dx);   centerx.move(dx); }
    void __st(const float dy) { bottom.move(dy); centery.move(dy); }
    void __sb(const float dy) { top.move(dy);    centery.move(dy); }

    void __scx(const float dx){ left.move(dx);     right.move(dx); }
    void __scy(const float dy){ top.move(dy);     bottom.move(dy); }

    void __sw(const float dw) { right.move(dw);  centerx.move(dw / 2); }
    void __sh(const float dh) { bottom.move(dh); centery.move(dh / 2); }
};
*/
#endif // UTIL_AABB_H
