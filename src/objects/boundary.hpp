#ifndef OBJ_BOUNDARY_HPP
#define OBJ_BOUNDARY_HPP

#include "game_object.hpp"

class Boundary: public GameObject
{
public:
    Boundary(const sf::IntRect rect);
    Boundary(const sf::IntRect rect, const sf::Color c);
    void render(sf::RenderWindow &window) override;
    const sf::Vector2f getPosition() const;
    const sf::Vector2i getSize() const;
    const sf::FloatRect getRect() const;

private:
    CollisionGroup col_group;
    sf::IntRect rect;
    sf::RectangleShape shape;
    sf::Color color;
};

#endif // OBJ_BOUNDARY_HPP
