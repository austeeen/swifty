#include "ai_object.hpp"

AiObject::AiObject(const GameObjectAsset ast):
    GameObject(ast)
{
    cmpts[typeid(AiController)] = std::make_shared<AiController>(this);
    cmpts[typeid(PathingVSI)] = std::make_shared<PathingVSI>(this);
    // todo add new los component or create los shape
    m_home = ast.start_pos;
}
void AiObject::setState(const ObjectState next_state)
{
    GameObject::setState(next_state);
    this->cmpnt<AiController>()->setState(cur_state);
}
void AiObject::setTarget(GameObject* target)
{
    // out::debug("AiObject::setTarget", target->getName().c_str());
    m_target = target;
}
void AiObject::setAiZone(const sf::IntRect& zone)
{
    // out::debug("AiObject::setAiZone");
    cmpnt<PathingVSI>()->setZone(zone);
}

/* actions */

void AiObject::noAction()
{
    // out::debug("AiObject::noAction");
    return;
}
void AiObject::attackTarget()
{
    // todo
    // out::debug("AiObject::attackTarget");
    return;
}
void AiObject::clearDestination()
{
    // out::debug("AiObject::clearDestination");
    cmpnt<PathingVSI>()->clearDestination();
}
void AiObject::setPathFromZone()
{
    // out::debug("AiObject::setPathFromZone");
    cmpnt<PathingVSI>()->newDestination();
}
void AiObject::setPathToTarget()
{
    // out::debug("AiObject::setPathToTarget");
    const sf::FloatRect tpos = m_target->getPositionRect();
    cmpnt<PathingVSI>()->setDestination(sf::Vector2f(tpos.left + (tpos.width / 2), tpos.top + (tpos.height / 2)));
}
void AiObject::setPathToHome()
{
    // out::debug("AiObject::setPathToHome");
    cmpnt<PathingVSI>()->setDestination(m_home);
}
void AiObject::redrawPath()
{
    // out::debug("AiObject::redrawPath");
    // cmpnt<PathingVSI>()->redrawPath();
    cmpnt<PathingVSI>()->newDestination();
}

/* conditions */
bool AiObject::hasDestination() const
{
    // out::debug("AiObject::hasDestination");
    return cmpnt<PathingVSI>()->hasDestination();
}
bool AiObject::targetDetected() const
{
    // out::debug("AiObject::targetDetected");
    // todo check m_target against los component or shape?
    return false;
}
bool AiObject::closeToDestination() const
{
    // out::debug("AiObject::closeToDestination");
    return cmpnt<RigidBody>()->closeTo(cmpnt<PathingVSI>()->getDestination());
}
bool AiObject::closeToTarget() const
{
    // out::debug("AiObject::closeToTarget");
    return cmpnt<RigidBody>()->closeTo(m_target->getPositionRect());
}
bool AiObject::closeToHome() const
{
    // out::debug("AiObject::closeToHome");
    return cmpnt<RigidBody>()->closeTo(m_home);
}
bool AiObject::isStuck() const
{
    // out::debug("AiObject::isStuck");
    return cmpnt<AiController>()->stuckTimedout();
}
