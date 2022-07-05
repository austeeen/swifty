#ifndef CMP_SPRITE_HPP
#define CMP_SPRITE_HPP

#include "component_base.hpp"

class RigidBody;

class Sprite: public Component
{
public:
    Sprite(GameObject* obj);
    void build() override;
    void setUp() override;
    void render(sf::RenderWindow &window) override;
    void setTextureRect(const sf::IntRect& texture_rect);
    void flipTexture(bool facing_right);

private:
    void updateTextureRect();

    sf::Texture img_texture;
    sf::IntRect cur_rect;
    bool flip_texture;
    sf::Sprite sprite;
};

#endif // CMP_SPRITE_HPP
