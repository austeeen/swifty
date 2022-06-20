#include "assets.hpp"

GameObjectAsset::GameObjectAsset(const TileObject& obj):
    img_texture(obj.img_texture),
    size(obj.tilesize),
    rect(sf::Vector2f(0, 0), (sf::Vector2f) obj.tilesize),
    coeffs(obj.pCoeffs),
    animation_rolls(obj.animation_rolls)
{
     start_pos = sf::Vector2f(CAT_START_X * obj.tilesize.x, CAT_START_Y * obj.tilesize.y);
}
