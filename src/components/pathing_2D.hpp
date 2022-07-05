#ifndef CMP_PATHING_2D_HPP
#define CMP_PATHING_2D_HPP

#include "component_base.hpp"

// featuring a 'VSI' -- very simple implementation for now

class PathingVSI: public Component
{
public:
    PathingVSI(GameObject* obj);
    void update(const float dt) override;

    void setZone(const sf::IntRect& zone);
    void newDestination();
    void setDestination(const sf::Vector2f& dest);
    void clearDestination();
    const sf::Vector2f getDestination() const;
    const bool hasDestination() const;

private:
    int last_dt; // to seed random numbers
    sf::IntRect m_zone;
    sf::Vector2f m_destination;
};

class Pathing2D: public Component
{
public:
    Pathing2D(GameObject* obj);
    void setUp() override;
    void update(const float dt) override;

    void setZone(const sf::IntRect& zone);
    void clearPath();
    void drawPath();
    void redrawPath();
    void clearDestination();
    void createDestination();
    void setDestination(const sf::FloatRect& dest);

    const sf::Vector2f getDestination() const;
    const bool hasDestination() const;

private:
    sf::FloatRect m_bounds;
    Waypoint* m_root;
    Waypoint* m_node;

    // VSI
    sf::IntRect m_zone;
};

#endif // CMP_PATHING_2D_HPP
