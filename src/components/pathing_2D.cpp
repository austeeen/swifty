#include "pathing_2D.hpp"
#include "../objects/game_object.hpp"

Pathing2D::Pathing2D(GameObject* obj):
    Component(obj)
{}
void Pathing2D::setUp()
{
    m_bounds = obj->getAsset().pathing_zone;
}
void Pathing2D::update(const float dt)
{
    if (m_node == nullptr) {
        return;
    } else if (obj->cmpnt<RigidBody>()->contains(m_node->loc)) {
        m_node = m_node->next;
    }
}
void Pathing2D::clearPath()
{
    m_node = nullptr;

    // todo delete or use shared_ptr and remove waypoint connections
    m_root = nullptr;
}
void Pathing2D::drawPath()
{
    if (m_root != nullptr) {
        clearPath();
    }
    // todo set up m_root given m_bounds
    // root == final waypoint and the waypoint nodes are linked backwards
    m_node = m_root;
}
void Pathing2D::createDestination()
{
    // todo create destination from pathing zone
    drawPath();
}
const sf::Vector2f Pathing2D::getDestination() const
{
    return m_root == nullptr ? sf::Vector2f(0, 0) : m_root->loc;
}
const bool Pathing2D::hasDestination() const
{
    return m_root != nullptr;
}
