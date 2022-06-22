#include "assets.hpp"

GameObjectAsset::GameObjectAsset(const TsxBaseObject& tsx_obj):
    img_texture(tsx_obj.img_texture),
    size(tsx_obj.tilesize)
{}

PlayerObjectAsset::PlayerObjectAsset(const TileObject& tsx_obj):
    GameObjectAsset(tsx_obj),
    coeffs(tsx_obj.pCoeffs),
    animation_rolls(tsx_obj.animation_rolls)
{
     start_pos = sf::Vector2f(CAT_START_X * size.x, CAT_START_Y * size.y);
}

PlatformObjectAsset::PlatformObjectAsset(const DynamicTiledObject& tsx_obj):
    GameObjectAsset(tsx_obj),
    collider(tsx_obj.collider),
    speed(tsx_obj.speed),
    dest(tsx_obj.dest),
    horizontal(tsx_obj.horizontal)
{
     start_pos = sf::Vector2f(tsx_obj.position_rect.left, tsx_obj.position_rect.top);
}
