#ifndef CMP_SPRITE_HPP
#define CMP_SPRITE_HPP

#include "c_base.hpp"

class RigidBody;

class Sprite: public Component
{
public:
    Sprite(GameObject* obj);
    void build() override;
    void render(sf::RenderWindow &window) override;
    void setTextureRect(const sf::IntRect& texture_rect);
    void setFacing(bool facing_right);

private:
    void updateTextureRect();

    sf::Texture img_texture;
    sf::IntRect cur_rect;
    bool facing_right;
    sf::Sprite sprite;
};

#endif // CMP_SPRITE_HPP
