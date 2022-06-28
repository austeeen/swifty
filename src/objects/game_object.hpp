#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include "object_bases.hpp"

class GameObject : public KinematicObject, public ComponentType
{
public:
    GameObject(const GameObjectAsset ast);
    void setStartPosition(const int x, const int y);
    const GameObjectAsset& getAsset() const;
    void toggleRects();
    const std::string& getName() const override;
    const CollisionRect& getCollider() const override;
    const std::vector<sf::Vector2f>& getColliders() const override;
    void onColliding(const sf::Vector2f& offset, const ColliderType m_type, const ColliderType b_type) const override;
    void updateInertia(const sf::Vector2f& intertia) const override;
    const sf::Vector2f& getVelocity() const override;
    
protected:
    ObjectState cur_state;
    GameObjectAsset ast;

};

#endif // GAMEOBJECT_HPP
