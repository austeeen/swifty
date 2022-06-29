#include "assets.hpp"

ObjectAssetBase::ObjectAssetBase(std::shared_ptr<TsxBaseObject> tsx_obj):
    size(tsx_obj->tilesize)
{}

GameObjectAsset::GameObjectAsset(std::shared_ptr<TileObject> tsx_obj):
    ObjectAssetBase(tsx_obj),
    name(tsx_obj->name),
    coeffs(tsx_obj->pCoeffs),
    animation_rolls(tsx_obj->animation_rolls),
    pathing_zone(tsx_obj->pathing_zone)
{
    img_texture = tsx_obj->img_texture;
    start_pos = sf::Vector2f(CAT_START_X * size.x, CAT_START_Y * size.y);
}

PlatformObjectAsset::PlatformObjectAsset(std::shared_ptr<DynamicTiledObject> tsx_obj):
    ObjectAssetBase(tsx_obj),
    name(tsx_obj->name),
    position_rect(tsx_obj->position_rect),
    collider(tsx_obj->collider),
    speed(tsx_obj->speed),
    root_waypoint(tsx_obj->root_waypoint)
{
    img_texture = tsx_obj->render_texture->getTexture();
    start_pos = sf::Vector2f(tsx_obj->position_rect.left, tsx_obj->position_rect.top);
}
