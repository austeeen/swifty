#include "aabb.hpp"

/**************************************************************************************************/
/* VAL */
AABB::val::val(AABB *r, const float v, moveFunc _mf):
    r(r), mv(v), mf(_mf)
{};
AABB::val& AABB::val::operator=(const val& v)
{
    (r->*mf)((float)v - mv);
    mv = (float) v;
    return *this;
}
AABB::val& AABB::val::operator=(const float v)
{
    (r->*mf)(v - mv);
    mv = v;
    return *this;
}
AABB::val& AABB::val::operator+=(const val& dv)
{
    (r->*mf)((float) dv);
    mv += (float) dv;
    return *this;
}
AABB::val& AABB::val::operator+=(const float dv)
{
    (r->*mf)(dv);
    mv += dv;
    return *this;
}
AABB::val& AABB::val::operator-=(const val& dv)
{
    (r->*mf)(-(float) dv);
    mv -= (float) dv;
    return *this;
}
AABB::val& AABB::val::operator-=(const float dv)
{
    (r->*mf)(-dv);
    mv -= dv;
    return *this;
}
AABB::val::operator bool() const
{
    return mv != 0;
}
AABB::val::operator float() const
{
    return mv;
}
AABB::val::operator std::string() const
{
    return std::to_string(mv);
}
void AABB::val::move(const float d)
{
    mv += d;
}
void AABB::val::set(const float d)
{
    mv = d;
}

/* POINT */

AABB::vec::vec(const val& x, const val& y):
x(x), y(y)
{}
AABB::vec& AABB::vec::operator=(const AABB::vec& v)
{
    x = v.x;
    y = v.y;
    return *this;
}
AABB::vec::operator bool() const
{
    return (float)x != 0 && (float)y != 0;
}
AABB::vec::operator sf::Vector2f() const
{
    return sf::Vector2f((float) x, (float) y);
}
AABB::vec::operator std::string() const
{
    return "(" + (std::string) x + ", " + (std::string) y + ")";
}

/* RECT */

AABB::AABB(): AABB(0.f, 0.f, 0.f, 0.f)
{}
AABB::AABB(const AABB& r) :
left      (this, (float)r.left,                         &AABB::__sl ),
right     (this, (float)r.left + (float)r.width,        &AABB::__sr ),
top       (this, (float)r.top,                          &AABB::__sb ),
bottom    (this, (float)r.top  + (float)r.height,       &AABB::__st ),
width     (this, (float)r.width,                        &AABB::__sw ),
height    (this, (float)r.height,                       &AABB::__sh ),
center(val(this, (float)r.left + ((float)r.width / 2),  &AABB::__scx),
       val(this, (float)r.top  + ((float)r.height / 2), &AABB::__scy)),
pos       (left, top)
{}
AABB::AABB(const float x, const float y, const float w, const float h) :
left   (this, x,           &AABB::__sl ),
right  (this, x + w,       &AABB::__sr ),
top    (this, y,           &AABB::__sb ),
bottom (this, y + h,       &AABB::__st ),
width  (this, w,           &AABB::__sw ),
height (this, h,           &AABB::__sh ),
center(val(this, x + (w / 2), &AABB::__scx),
       val(this, y + (h / 2), &AABB::__scy)),
pos       (left, top)
{}
AABB::AABB(const sf::FloatRect& fr) :
AABB(fr.top, fr.left, fr.width, fr.height)
{}
AABB::AABB(const sf::Vector2f &p, const sf::Vector2f &s) :
AABB(p.x, p.y, s.x, s.y)
{};
AABB& AABB::operator=(const AABB &r)
{
    left.set(r.left);
    right.set(r.right);
    top.set(r.top);
    width.set(r.width);
    height.set(r.height);
    bottom.set(r.bottom);
    center.x.set(r.center.x);
    center.y.set(r.center.y);
    return *this;
}
void AABB::setPosition(const sf::Vector2f& p)
{
    this->left = p.x;
    this->top = p.y;
}
void AABB::setPosition(const float x, const float y)
{
    this->left = x;
    this->top = y;
}
void AABB::setSize(const sf::Vector2f& s)
{
    this->width = s.x;
    this->height = s.y;
}
void AABB::setSize(const float x, const float y)
{
    this->width = x;
    this->height = y;
}
void AABB::setCenter(const sf::Vector2f& c)
{
    this->center.x = c.x;
    this->center.y = c.y;
}
void AABB::setCenter(const float x, const float y)
{
    this->center.x = x;
    this->center.y = y;
}
sf::Vector2f AABB::getSize() const
{
    return sf::Vector2f(width, height);
}
sf::Vector2f AABB::getPosition() const
{
    return sf::Vector2f(left, top);
}
AABB::operator sf::FloatRect() const
{
    return sf::FloatRect(left, top, width, height);
}
AABB::operator std::string() const
{
    std::string str;
    sprintf((char *) &str.c_str()[0], "[%f, %f, %f, %f] (%f, %f)",
            (float) left, (float) top, (float) right, (float) bottom, (float) width, (float) height);
    return str;
}
AABB::operator bool() const
{
    return (float) width != 0 && (float) height != 0;
}
AABB AABB::clip(const AABB &a, const AABB &b)
{
    float dx = 0.0, dy = 0.0;

    if (b.left > a.left) {
        dx = b.left - a.right; // dy < 0
    } else {
        dx = b.right - a.left; // dx > 0
    }
    if (b.top > a.top) {
        dy = b.top - a.bottom; // dy < 0
    } else {
        dy = b.bottom - a.top; // dy > 0
    }
    return AABB(0.0, 0.0, dx, dy);
}
AABB AABB::clip(const AABB &AABB) const
{
    return AABB::clip(*this, AABB);
}
