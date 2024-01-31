#include "pathing_2D.hpp"
#include "../objects/game_object.hpp"

PathingVSI::PathingVSI(GameObject* obj): Component(obj)
{}
void PathingVSI::update(const float dt)
{
    last_dt = dt * 100000;
    if (!hasDestination()) {
        // out::debug("PathingVSI::update", "Spider has no destination");
        return;
    } else if (obj->cmpnt<RigidBody>()->intersects(m_destination)) {
        out::debug("PathingVSI::update", "Spider reached destination");
        clearDestination();
        obj->stopAll();
    } else {
        const sf::FloatRect posrect = obj->getPositionRect();
        if (posrect.left < m_destination.x && posrect.left + posrect.width < m_destination.x) {
            obj->stop(Dir4::left);
            obj->move(Dir4::right);
            out::debug("PathingVSI::update", "Spider moving right");
        } else {
            obj->stop(Dir4::right);
            obj->move(Dir4::left);
            out::debug("PathingVSI::update", "Spider moving left");
        }
    }
}
void PathingVSI::setZone(const sf::IntRect& zone)
{
    out::debug("PathingVSI::setZone", "(%d, %d, %d, %d)", zone.left, zone.top, zone.width, zone.height);
    m_zone = zone;
}
void PathingVSI::newDestination()
{
    srand(last_dt);
    m_destination.y = m_zone.top - (m_zone.height / 2);
    m_destination.x = (rand() % m_zone.width) + m_zone.left;
    out::debug("PathingVSI::newDestination", "(%f, %f)", m_destination.x, m_destination.y);
}
void PathingVSI::setDestination(const sf::Vector2f& dest)
{
    m_destination = dest;
    out::debug("PathingVSI::setDestination", "(%f, %f)", m_destination.x, m_destination.y);
}
void PathingVSI::clearDestination()
{
    m_destination.x = 0.f;
    m_destination.y = 0.f;
    out::debug("PathingVSI::clearDestination", "(%f, %f)", m_destination.x, m_destination.y);
}
const sf::Vector2f PathingVSI::getDestination() const
{
    return m_destination;
}
const bool PathingVSI::hasDestination() const
{
    return m_destination.x != 0.f && m_destination.y != 0.f;
}

/**************************************************************************************************/

Pathing2D::Pathing2D(GameObject* obj):
    Component(obj)
{}
void Pathing2D::setUp()
{
    // m_bounds = obj->getAsset().pathing_zone;
}
void Pathing2D::update(const float dt)
{
    if (m_node == nullptr) {
        return;
    } else if (obj->cmpnt<RigidBody>()->intersects(m_node->loc)) {
        m_node = m_node->next;
    }
}
void Pathing2D::setZone(const sf::IntRect& zone)
{
    m_zone = zone;
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
void Pathing2D::redrawPath()
{
    // to do
    if (m_root != nullptr) {
        clearPath();
    }
    // root == final waypoint and the waypoint nodes are linked backwards
    m_node = m_root;
}
void Pathing2D::createDestination()
{
    // todo create destination from pathing zone
}
void Pathing2D::setDestination(const sf::FloatRect& dest)
{
    // todo create destination from given dest rect
    // m_root->loc = dest.center ?
}
const sf::Vector2f Pathing2D::getDestination() const
{
    return m_root == nullptr ? sf::Vector2f(0, 0) : m_root->loc;
}
const bool Pathing2D::hasDestination() const
{
    return m_root != nullptr;
}
