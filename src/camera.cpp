#include "camera.hpp"

Camera::Camera(const sf::FloatRect view_rect):
view(view_rect)
{}
void Camera::update(const sf::Vector2u window_size)
{
    win_size = window_size;
    float windowRatio = win_size.x / (float) win_size.y;
    float viewRatio = view.getSize().x / (float) view.getSize().y;
    float sizeX = 1;
    float sizeY = 1;
    float posX = 0;
    float posY = 0;
    if (windowRatio < viewRatio) {
        sizeX = viewRatio / windowRatio;
        posX = (1 - sizeX) / 2.f;
    } else {
        sizeY = windowRatio / viewRatio;
        posY = (1 - sizeY) / 2.f;
    }
    view.setViewport( sf::FloatRect(posX, posY, sizeX, sizeY) );
}
void Camera::setCenter(const sf::Vector2f center)
{
    view.setCenter(center);
}
void Camera::applyView(sf::RenderWindow& window)
{
    window.setView(view);
}
