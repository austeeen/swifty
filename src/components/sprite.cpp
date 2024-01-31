#include "sprite.hpp"
#include "../objects/game_object.hpp"

Sprite::Sprite(GameObject* obj):
Component(obj), cur_rect(0, 0, 0, 0), flip_texture(false)
{}
void Sprite::build()
{
    sprite.setTexture(obj->getAsset().img_texture);
}
void Sprite::setUp()
{
    updateTextureRect();
}
void Sprite::setTextureRect(const sf::IntRect &texture_rect)
{
    cur_rect = texture_rect;
    updateTextureRect();
}
void Sprite::flipTexture(bool f)
{
    if (flip_texture == f) {
        return;
    } 
    // else if (f) {
    //     out::debug("Sprite::flipTexture", obj->getName().c_str());
    // } else {
    //     out::debug("Sprite::flipTexture", "%s unflipped", obj->getName().c_str());
    // }
    flip_texture = f;
    updateTextureRect();
}
void Sprite::updateTextureRect()
{
    if (flip_texture) {
        cur_rect.left += cur_rect.width;
        cur_rect.width = -cur_rect.width;
    }
    sprite.setTextureRect(cur_rect);
}
void Sprite::render(sf::RenderWindow &window)
{
    sf::Vector2f p = this->obj->cmpnt<RigidBody>()->getPosition();
    sprite.setPosition(p);
    window.draw(sprite);
}
