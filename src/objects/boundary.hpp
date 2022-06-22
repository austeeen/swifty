#ifndef OBJ_BOUNDARY_HPP
#define OBJ_BOUNDARY_HPP

#include "game_object.hpp"

class Boundary: public StaticObject
{
public:
    Boundary(const sf::IntRect rect);
    const sf::Vector2f getPosition() const;
    const sf::Vector2i getSize() const;
    const sf::FloatRect getCollider() const override;

private:
    sf::IntRect rect;
};

#endif // OBJ_BOUNDARY_HPP
