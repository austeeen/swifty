#ifndef OBJ_AI_OBJECT_HPP
#define OBJ_AI_OBJECT_HPP

#include "game_object.hpp"

class AiObject: public GameObject
{
public:
    AiObject(const GameObjectAsset ast);

    void setState(const ObjectState next_state) override;
    void setTarget(GameObject* target);
    void setAiZone(const sf::IntRect& zone);

    // action hooks
    void noAction();
    void attackTarget();
    void clearDestination();
    void setPathFromZone();
    void setPathToTarget();
    void setPathToHome();
    void redrawPath();

    // condition hooks
    bool hasDestination() const;
    bool targetDetected() const;
    bool closeToDestination() const;
    bool closeToTarget() const;
    bool closeToHome() const;
    bool isStuck() const;

protected:

    GameObject* m_target;
    sf::Vector2f m_home;
};

#endif // OBJ_AI_OBJECT_HPP
