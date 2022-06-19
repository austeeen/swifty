#include "sprite.hpp"
#include "../objects/player.hpp"

Sprite::Sprite(Player* obj):
Component(obj), cur_rect(0, 0, 0, 0), facing_right(true)
{}
void Sprite::build()
{
    sprite.setTexture(obj->getAsset().img_texture);
}
void Sprite::setTextureRect(const sf::IntRect &texture_rect)
{
    cur_rect = texture_rect;
    updateTextureRect();
}
void Sprite::setFacing(bool facing)
{
    facing_right = facing;
    updateTextureRect();
}
void Sprite::updateTextureRect()
{
    if (!facing_right) {
        cur_rect.left += cur_rect.width;
        cur_rect.width = -cur_rect.width;
    }
    sprite.setTextureRect(cur_rect);
}
void Sprite::render(sf::RenderWindow &window)
{
    sprite.setPosition(this->obj->getPosition());
    window.draw(sprite);
}
