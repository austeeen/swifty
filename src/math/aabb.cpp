#include "aabb.hpp"

/**************************************************************************************************/
/* VAL */
rect::val::val(rect *r, const float v, void(rect::*_m)(const float)): r(r), mv(v), __move(_m)
{};
rect::val& rect::val::operator=(const val& v)
{
    (r->*__move)((float)v - mv);
    set((float)v);
    return *this;
}
rect::val& rect::val::operator=(const float v)
{
    (r->*__move)(v - mv);
    set(v);
    return *this;
}
rect::val& rect::val::operator+=(const float dv)
{
    (r->*__move)(dv);
    move(dv);
    return *this;
}
rect::val& rect::val::operator-=(const float dv)
{
    (r->*__move)(-dv);
    move(-dv);
    return *this;
}
rect::val::operator float() const
{
    return mv;
}
std::string rect::val::tostr() const
{
    return std::to_string(mv);
}
void rect::val::move(const float d)
{
    mv += d;
}
void rect::val::set(const float d)
{
    mv = d;
}

/* POINT */

rect::point::point(val *x, val *y):
xy{x, y}, x(x), y(y)
{}
rect::point& rect::point::operator=(const rect::point& v)
{
    *x = *v.x;
    *y = *v.y;
    return *this;
}
std::string rect::point::tostr() const
{
    return "(" + x->tostr() + ", " + y->tostr() + ")";
}
rect::point::operator sf::Vector2f() const
{
    return sf::Vector2f((float) *x, (float) *y);
}
rect::val& rect::point::operator[](const int i) const
{
    return *xy[i];
}
/* RECT */
rect::rect(): rect(0.f, 0.f, 0.f, 0.f)
{}
rect::rect(const float x, const float y, const float w, const float h) :
left   (this, x,           &rect::__sl ),
right  (this, x + w,       &rect::__sr ),
top    (this, y,           &rect::__sb ),
bottom (this, y + h,       &rect::__st ),
centerx(this, x + (w / 2), &rect::__scx),
centery(this, y + (h / 2), &rect::__scy),
width  (this, w,           &rect::__sw ),
height (this, h,           &rect::__sh ),
center(&centerx, &centery),
pos(&left, &top),
size(&width, &height)
{}
rect::rect(const sf::FloatRect& fr) :
rect(fr.top, fr.left, fr.width, fr.height)
{}
rect::rect(const sf::Vector2f &p, const sf::Vector2f &s) :
rect(p.x, p.y, s.x, s.y)
{};
rect::rect(const std::vector<float> &v) :
rect(v[0], v[1], v[2], v[3])
{};
rect::rect(const rect& r) :
left   (this, (float)r.left,                         &rect::__sl ),
right  (this, (float)r.left + (float)r.width,        &rect::__sr ),
top    (this, (float)r.top,                          &rect::__sb ),
bottom (this, (float)r.top  + (float)r.height,       &rect::__st ),
centerx(this, (float)r.left + ((float)r.width / 2),  &rect::__scx),
centery(this, (float)r.top  + ((float)r.height / 2), &rect::__scy),
width  (this, (float)r.width,                        &rect::__sw ),
height (this, (float)r.height,                       &rect::__sh ),
center(&centerx, &centery),
pos(&left, &top),
size(&width, &height)
{}
rect& rect::operator=(const rect &r)
{
    left.set(r.left);
    right.set(r.right);
    top.set(r.top);
    bottom.set(r.bottom);
    centerx.set(r.centerx);
    centery.set(r.centery);
    width.set(r.width);
    height.set(r.height);
    return *this;
}
void rect::setPosition(const sf::Vector2f& p)
{
    this->left = p.x;
    this->top = p.y;
}
void rect::setPosition(const float x, const float y)
{
    this->left = x;
    this->top = y;
}
void rect::setSize(const sf::Vector2f& s)
{
    this->width = s.x;
    this->height = s.y;
}
void rect::setSize(const float x, const float y)
{
    this->width = x;
    this->height = y;
}
void rect::setCenter(const sf::Vector2f& c)
{
    this->centerx = c.x;
    this->centery = c.y;
}
void rect::setCenter(const float x, const float y)
{
    this->centerx = x;
    this->centery = y;
}
sf::Vector2f rect::getSize() const
{
    return sf::Vector2f(width, height);
}
sf::Vector2f rect::getPosition() const
{
    return sf::Vector2f(left, top);
}
rect::operator sf::FloatRect() const
{
    return sf::FloatRect(left, top, width, height);
}
rect::operator sf::IntRect() const
{
    return sf::IntRect(left, top, width, height);
}
std::string rect::tostr() const
{
    return "[" + left.tostr() + ", " + top.tostr() + ", " + right.tostr() + ", " + bottom.tostr() + "], (" + width.tostr() + ", " + height.tostr() + ")";
}
rect rect::clip(const rect &a, const rect &b)
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
    return rect(0.0, 0.0, dx, dy);
}
rect rect::clip(const rect &rect) const
{
    return rect::clip(*this, rect);
}
const bool rect::exists() const
{
    return !(this->left == 0 && this->top == 0 && this->right == 0 && this->bottom == 0);
}
