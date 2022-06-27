#include "rect.hpp"
#include "utils.hpp"

/**************************************************************************************************/
/* VAL */

rect::val& rect::val::operator=(const val& v)
{
    other->move(v - mv);
    set((float) v);
    return *this;
}
rect::val& rect::val::operator=(const float v)
{
    other->move(v - mv);
    set(v);
    return *this;
}
rect::val& rect::val::operator+=(const float dv)
{
    other->move(dv);
    move(dv);
    return *this;
}
rect::val& rect::val::operator-=(const float dv)
{
    other->move(-dv);
    move(-dv);
    return *this;
}

/**************************************************************************************************/
/* RECT */

rect::rect(): rect(0.f, 0.f, 0.f, 0.f) {}
rect::rect(const float& l, const float& t, const float& w, const float& h):
left (this, l, &right),  right (this, l + w, &left),
top  (this, t, &bottom), bottom(this, t + h, &top),
width(this, w, &right),  height(this, h, &bottom)
{}
rect::rect(const sf::FloatRect& fr):
rect(fr.top, fr.left, fr.width, fr.height)
{}
rect::rect(const int x, const int y, const int w, const int h):
rect((float) x, (float) y, (float) w, (float) h)
{}
rect::rect(const sf::IntRect& fr):
rect(fr.top, fr.left, fr.width, fr.height)
{}
rect::rect(const rect& r):
left (this, (float)r.left,  &right),  right(this,  (float)r.right,  &left),
top  (this, (float)r.top,   &bottom), bottom(this, (float)r.bottom, &top),
width(this, (float)r.width, &right),  height(this, (float)r.height, &bottom)
{}
rect& rect::operator=(const rect &r)
{
    left.set(r.left);
    right.set(r.right);
    top.set(r.top);
    bottom.set(r.bottom);
    width.set(r.width);
    height.set(r.height);
    return *this;
}
void rect::operator+=(const rect& r)
{
    left.set(min(this->left,   r.left));
    top.set(min(this->top,    r.top));
    right.set(max(this->right,  r.right));
    bottom.set(max(this->bottom, r.bottom));
    width.set(this->right - this->left);
    height.set(this->bottom - this->top);
}
void rect::operator+=(const sf::FloatRect& r)
{
    *this += rect(r);
}
rect::operator bool() const
{
    return this->width != 0.f && this->height != 0.f;
}
rect::operator std::string() const
{
    std::stringstream ss;
    ss << (int) left << ", " << (int) top << ", " << (int) width << ", " << (int) height;
    return ss.str();
}
rect::operator sf::FloatRect() const
{
    return sf::FloatRect(left, top, width, height);
}
rect::operator sf::IntRect() const
{
    return sf::IntRect(left, top, width, height);
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
sf::Vector2f rect::getPosition() const
{
    return sf::Vector2f(left, top);
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
sf::Vector2f rect::getSize() const
{
    return sf::Vector2f(width, height);
}
void rect::setCenter(const sf::Vector2f& c)
{
    this->setCenter(c.x, c.y);
}
void rect::setCenter(const float x, const float y)
{
    this->left += x - (left + width / 2);
    this->top += y - (top + height / 2);
}
sf::Vector2f rect::getCenter() const
{
    return sf::Vector2f(left + width / 2, top + height / 2);
}
rect rect::clip(const rect &a, const rect &b)
{
    float dx = 0.f, dy = 0.f;
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
    return rect(0.f, 0.f, dx, dy);
}
rect rect::clip(const rect &rect) const
{
    return clip(*this, rect);
}
