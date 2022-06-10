#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "common.hpp"

class Camera
{
public:
    Camera(const sf::FloatRect view_rect);
    void update(const sf::Vector2u win_size);
    void setCenter(const sf::Vector2f center);
    void applyView(sf::RenderWindow &window);
    
private:
    sf::Vector2u win_size;
    sf::View view;
};

#endif // CAMERA_HPP
