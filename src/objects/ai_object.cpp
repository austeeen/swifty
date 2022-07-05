#include "ai_object.hpp"

AiObject::AiObject(const GameObjectAsset ast):
    GameObject(ast)
{
    cmpts[typeid(AiController)] = std::make_shared<AiController>(this);
    cmpts[typeid(PathingVSI)] = std::make_shared<PathingVSI>(this);
    // todo add new los component or create los shape
    m_home = ast.start_pos;
}
void AiObject::setState(const ObjectState s)
{
    printf("AiObject::setState %s\n", out::toStr(s).c_str());
    this->cmpnt<Animator>()->setState(cur_state);
    this->cmpnt<Physics2D>()->setState(cur_state);
    this->cmpnt<AiController>()->setState(cur_state);
}
void AiObject::setTarget(GameObject* target)
{
    printf("AiObject::setTarget %s\n", target->getName().c_str());
    m_target = target;
}
void AiObject::setAiZone(const sf::IntRect& zone)
{
    printf("AiObject::setAiZone\n");
    cmpnt<PathingVSI>()->setZone(zone);
}

void AiObject::noAction()
{
    printf("AiObject::noAction\n");
    return;
}
void AiObject::attackTarget()
{
    // todo
    printf("AiObject::attackTarget\n");
    return;
}
void AiObject::clearDestination()
{
    printf("AiObject::clearDestination\n");
    cmpnt<PathingVSI>()->clearDestination();
}
void AiObject::setPathFromZone()
{
    printf("AiObject::setPathFromZone\n");
    cmpnt<PathingVSI>()->newDestination();
}
void AiObject::setPathToTarget()
{
    printf("AiObject::setPathToTarget\n");
    const sf::FloatRect tpos = m_target->getPositionRect();
    cmpnt<PathingVSI>()->setDestination(sf::Vector2f(tpos.left + (tpos.width / 2), tpos.top + (tpos.height / 2)));
}
void AiObject::setPathToHome()
{
    printf("AiObject::setPathToHome\n");
    cmpnt<PathingVSI>()->setDestination(m_home);
}
void AiObject::redrawPath()
{
    printf("AiObject::redrawPath\n");
    // cmpnt<PathingVSI>()->redrawPath();
    cmpnt<PathingVSI>()->newDestination();
}


bool AiObject::hasDestination() const
{
    printf("AiObject::hasDestination\n");
    return cmpnt<PathingVSI>()->hasDestination();
}
bool AiObject::targetDetected() const
{
    printf("AiObject::targetDetected\n");
    // todo check m_target against los component or shape?
    return false;
}
bool AiObject::closeToDestination() const
{
    printf("AiObject::closeToDestination\n");
    return cmpnt<RigidBody>()->closeTo(cmpnt<PathingVSI>()->getDestination());
}
bool AiObject::closeToTarget() const
{
    printf("AiObject::closeToTarget\n");
    return cmpnt<RigidBody>()->closeTo(m_target->getPositionRect());
}
bool AiObject::closeToHome() const
{
    printf("AiObject::closeToHome\n");
    return cmpnt<RigidBody>()->closeTo(m_home);
}
bool AiObject::isStuck() const
{
    printf("AiObject::isStuck\n");
    return cmpnt<AiController>()->stuckTimedout();
}
