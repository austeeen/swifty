#ifndef CMP_PATHING_2D_HPP
#define CMP_PATHING_2D_HPP

#include "component_base.hpp"

class Pathing2D: public Component
{
public:
    Pathing2D(GameObject* obj);
    void setUp() override;
    void update(const float dt) override;

    void clearPath();
    void drawPath();

    void clearDestination();
    void createDestination();
    void setDestination(const sf::FloatRect& dest);

    const sf::Vector2f getDestination() const;
    const bool hasDestination() const;

private:
    sf::FloatRect m_bounds;
    Waypoint* m_root;
    Waypoint* m_node;
};

#endif // CMP_PATHING_2D_HPP
