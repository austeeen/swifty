#include "boundary.hpp"

Boundary::Boundary(const sf::IntRect rect):
    GameObject(CollisionGroup::floor),
    rect(rect),
    shape(sf::Vector2f(rect.width, rect.height))
{
    shape.setPosition(rect.left, rect.top);
}
Boundary::Boundary(const sf::IntRect rect, const sf::Color c):
    Boundary(rect)
{
    shape.setFillColor(color);
}
void Boundary::render(sf::RenderWindow &window)
{
    window.draw(shape);
}
const sf::Vector2f Boundary::getPosition() const
{
    return sf::Vector2f(rect.left, rect.top);
}
const sf::Vector2i Boundary::getSize() const
{
    return sf::Vector2i(rect.width, rect.height);
}
const sf::FloatRect Boundary::getRect() const
{
    return (sf::FloatRect) rect;
}
