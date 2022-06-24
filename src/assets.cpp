#include "assets.hpp"

GameObjectAsset::GameObjectAsset(std::shared_ptr<TsxBaseObject> tsx_obj):
    size(tsx_obj->tilesize)
{}

PlayerObjectAsset::PlayerObjectAsset(std::shared_ptr<TileObject> tsx_obj):
    GameObjectAsset(tsx_obj),
    coeffs(tsx_obj->pCoeffs),
    animation_rolls(tsx_obj->animation_rolls)
{
    img_texture = tsx_obj->img_texture;
    start_pos = sf::Vector2f(CAT_START_X * size.x, CAT_START_Y * size.y);
}

PlatformObjectAsset::PlatformObjectAsset(std::shared_ptr<DynamicTiledObject> tsx_obj):
    GameObjectAsset(tsx_obj),
    position_rect(tsx_obj->position_rect),
    collider(tsx_obj->collider),
    speed(tsx_obj->speed),
    waypoints(tsx_obj->waypoints)
{
    img_texture = tsx_obj->render_texture->getTexture();
    start_pos = sf::Vector2f(tsx_obj->position_rect.left, tsx_obj->position_rect.top);
}
