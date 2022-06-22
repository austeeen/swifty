#include "boundary.hpp"

Boundary::Boundary(const sf::IntRect rect):
    rect(rect)
{}
const sf::Vector2f Boundary::getPosition() const
{
    return sf::Vector2f(rect.left, rect.top);
}
const sf::Vector2i Boundary::getSize() const
{
    return sf::Vector2i(rect.width, rect.height);
}
const sf::FloatRect Boundary::getCollider() const
{
    return (sf::FloatRect) rect;
}
