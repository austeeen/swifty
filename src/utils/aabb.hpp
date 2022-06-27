#ifndef UTIL_AABB_H
#define UTIL_AABB_H

#include <SFML/Graphics.hpp>

struct rect
{

/**************************************************************************************************/

    struct val
    {
        val(rect *r, const float v, val* o): r(r), mv(v), other(o) {};
        val& operator=(const val& v);
        val& operator=(const float v);
        val& operator+=(const float dv);
        val& operator-=(const float dv);
        operator float() const { return mv; };
        std::string tostr() const { return std::to_string(mv); };
        void move(const float d) { mv += d; };
        void set(const float d) { mv = d; };
    private:
        rect *r;
        float mv;
        val* other;
    };

/**************************************************************************************************/

    rect();
    rect(const float& l, const float& t, const float& w, const float& h);
    rect(const sf::FloatRect& r);
    rect(const int x, const int y, const int w, const int h);
    rect(const sf::IntRect& fr);
    rect(const rect& r);

    rect& operator=(const rect &r);
    rect& operator+=(const rect& r);
    void operator+=(const sf::FloatRect& r);
    operator sf::FloatRect() const;
    operator sf::IntRect() const;
    operator bool() const;

    inline void move(float x, float y) {
        this->left += x;
        this->top  += y;
    }

    void setPosition(const sf::Vector2f& p);
    void setPosition(const float x, const float y);
    sf::Vector2f getPosition() const;

    void setSize(const sf::Vector2f& s);
    void setSize(const float x, const float y);
    sf::Vector2f getSize() const;

    void setCenter(const sf::Vector2f& c);
    void setCenter(const float x, const float y);
    sf::Vector2f getCenter() const;

    std::string tostr() const;
    static rect clip(const rect &a, const rect &b);
    rect clip(const rect &rect) const;

    val left, right, top, bottom, width, height;

private:
    void __sl(const float dx) { right.move(dx);  }
    void __sr(const float dx) { left.move(dx);   }
    void __st(const float dy) { bottom.move(dy); }
    void __sb(const float dy) { top.move(dy);    }
    void __sw(const float dw) { right.move(dw);  }
    void __sh(const float dh) { bottom.move(dh); }
};

#endif // UTIL_AABB_H
