#include "ai_behavior.hpp"
#include "../objects/all.hpp"

void testTree()
{
    /*
    [start]--pass-->[loc1]--pass-->[loc2]--pass-->[done]
       \               \              \
       fail            fail           fail
         \               \              \
       [start]         [start]        [start]
    */

    MoveToRect* start = new MoveToRect(sf::FloatRect(0, 0, 10, 10));
    start->pass = new MoveToRect(sf::FloatRect(50, 0, 10, 10));
    sf::IntRect loc1(50, 0, 10, 10);
    sf::IntRect loc2(0, 50, 10, 10);

    // start pos
    sf::IntRect ai(0, 0, 10, 10);

}
MoveToRect::MoveToRect(const sf::FloatRect& dest):
    m_dest(dest)
{}
void MoveToRect::enter(GameObject* obj)
{
    obj->setState(ObjectState::running);
    // obj->cmpnt<PathControl>()->setDestination(m_dest);
}
void MoveToRect::exit(GameObject* obj)
{
    // obj->cmpnt<PathControl>()->clearDestination();
}
bool MoveToRect::execute(GameObject* obj)
{
    return !obj->cmpnt<RigidBody>()->overlapping(m_dest);
}

AiBehavior::AiBehavior(GameObject* obj):
    Component(obj)
{

}
void AiBehavior::build()
{

}
void AiBehavior::setUp()
{

}
void AiBehavior::update(const float dt)
{

}
