#ifndef CMP_RIGID_BODY_HPP
#define CMP_RIGID_BODY_HPP

#include "component_base.hpp"

class RigidBody: public Component
{
public:
    RigidBody(GameObject* ast);
    void setUp() override;
    void render(sf::RenderWindow &window) override;

    void toggleDisplay();

    void move(const float x, const float y);

    void setColliders(const std::vector<CollisionRect>& rects);
    void updateFacing(const Dir4 next_facing);
    void xCollision(const float offset);
    void yCollision(const float offset);

    bool overlapping(const sf::FloatRect& rect) const;
    const sf::Vector2f getPosition() const;
    const sf::Vector2i getSize() const;
    const std::vector<CollisionRect>& getColliders() const;

private:
    void updateColliders();
    void faceLeft();
    void faceRight();
    sf::RectangleShape createShape(sf::Color c);

    Dir4 cur_facing;

    sf::FloatRect position_rect;
    std::vector<CollisionRect> collision_rects;
    CollisionRect* m_body_collider;
    sf::RectangleShape pos_shape;
    std::vector<sf::RectangleShape> collision_shapes;
    bool display_body;
};

#endif // CMP_RIGID_BODY_HPP
