#ifndef OBJ_MOVING_PLTFRM_HPP
#define OBJ_MOVING_PLTFRM_HPP

#include "game_object.hpp"


class MovingPlatform : public DynamicObject
{
public:
    MovingPlatform(const PlatformObjectAsset& ast);
    ~MovingPlatform();
    void setUp() override;
    void update(const float dt) override;
    void lateUpdate() override;
    void render(sf::RenderWindow&) override;

    void move(const float dx, const float dy);
    void toggleDisplay();

    const CollisionRect& getCollider() const override;
    const sf::Vector2f& getVelocity() const override;

private:
    void nextWaypoint();

    const PlatformObjectAsset ast;
    sf::Sprite* sprite;
    CollisionRect collider;
    sf::FloatRect position_rect;
    sf::Vector2f vel;
    Waypoint* wp;
    bool traversing;
    sf::RectangleShape pos_shape, col_shape;
    bool display_body;
};

#endif // OBJ_MOVING_PLTFRM_HPP
