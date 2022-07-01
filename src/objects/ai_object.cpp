#include "ai_object.hpp"

AiObject::AiObject(const GameObjectAsset ast):
    GameObject(ast)
{
    cmpts[typeid(AiController)] = std::make_shared<AiController>(this);
    cmpts[typeid(Pathing2D)] = std::make_shared<Pathing2D>(this);
    // todo add new los component or create los shape
    // todo set m_home = start position
}
void AiObject::setTarget(GameObject* target)
{
    m_target = target;
}


void AiObject::noAction()
{
    return;
}
void AiObject::attackTarget()
{
    // todo
    return;
}
void AiObject::clearDestination()
{
    cmpnt<Pathing2D>()->clearPath();
}
void AiObject::setPathFromZone()
{
    cmpnt<Pathing2D>()->createDestination();
    cmpnt<Pathing2D>()->drawPath();
}
void AiObject::setPathToTarget()
{
    cmpnt<Pathing2D>()->setDestination(m_target->getPositionRect());
    cmpnt<Pathing2D>()->drawPath();
}
void AiObject::setPathToHome()
{
    cmpnt<Pathing2D>()->setDestination(m_home);
    cmpnt<Pathing2D>()->drawPath();
}
void AiObject::redrawPath()
{
    cmpnt<Pathing2D>()->redrawPath();
}


bool AiObject::hasDestination() const
{
    return cmpnt<Pathing2D>()->hasDestination();
}
bool AiObject::targetDetected() const
{
    // todo check m_target against los component or shape?
    return false;
}
bool AiObject::closeToDestination() const
{
    return cmpnt<RigidBody>()->closeTo(cmpnt<Pathing2D>()->getDestination());
}
bool AiObject::closeToTarget() const
{
    return cmpnt<RigidBody>()->closeTo(m_target->getPositionRect());
}
bool AiObject::closeToHome() const
{
    return cmpnt<RigidBody>()->closeTo(m_home);
}
bool AiObject::isStuck() const
{
    return cmpnt<AiController>()->stuckTimedout();
}
