#ifndef OBJ_AI_OBJECT_HPP
#define OBJ_AI_OBJECT_HPP

#include "game_object.hpp"

class AiObject: public GameObject
{
public:
    AiObject(const GameObjectAsset ast);

    void noAction();

    void setTarget(GameObject* target);
    void newDestination();
    void clearDestination();

    void setPathToTarget();
    void setPathToHome();

    bool hasDestination() const;

    bool targetDetected() const;

    bool closeToDestination() const;
    bool closeToTarget() const;
    bool closeToHome() const;

    bool isStuck() const;

protected:
    GameObject* m_target;
    sf::FloatRect m_home;
};

#endif // OBJ_AI_OBJECT_HPP
