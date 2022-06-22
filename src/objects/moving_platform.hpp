#ifndef OBJ_MOVING_PLTFRM_HPP
#define OBJ_MOVING_PLTFRM_HPP

#include "game_object.hpp"


class MovingPlatform : public DynamicObject
{
public:
    MovingPlatform(const PlatformObjectAsset& ast);
    void setUp() override;
    void update(const float dt) override;
    void render(sf::RenderWindow&) override;

    void move(const float dx, const float dy);
    void toggleDisplay();

    const CollisionRect& getCollider() const override;

private:
    const PlatformObjectAsset ast;
    CollisionRect collider;
    sf::FloatRect position_rect;
    sf::Vector2f vel, cur_dest;
    sf::Sprite sprite;
    sf::RectangleShape pos_shape, col_shape;
    bool display_body;
};

#endif // OBJ_MOVING_PLTFRM_HPP
