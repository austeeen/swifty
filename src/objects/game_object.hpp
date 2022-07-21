#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include "object_bases.hpp"

class GameObject : public ObjectBase
{
public:
    GameObject(const GameObjectAsset ast);
    void build();
    void setUp() override;
    void update(const float dt) override;
    void lateUpdate() override;
    void render(sf::RenderWindow &window) override;

    void toggleDisplay() override;
    
    void move(const Dir4 d);
    void stop(const Dir4 d);
    void stopAll();

    virtual void setState(const ObjectState s);
    void setStartPosition(const int x, const int y);

    void onColliding(const sf::Vector2f& offset, const ColliderType m_type, const ColliderType b_type) const;
    void updateInertia(const sf::Vector2f& inertia) const;

    const std::string& getName() const;
    const GameObjectAsset& getAsset() const;
    const Dir4 getOrientation() const;
    const sf::FloatRect& getPositionRect() const;
    const std::vector<CollisionRect>& getColliders() const;
    const sf::Vector2f& getVelocity() const;

    template <typename T> std::shared_ptr<T> cmpnt() const {
        if (cmpts.count(typeid(T)) == 0)
            return nullptr;
        return std::dynamic_pointer_cast<T>(cmpts.at(typeid(T)));
    }

protected:
    std::map<std::type_index, std::shared_ptr<Component>> cmpts;
    ObjectState cur_state;
    GameObjectAsset ast;
    const Dir4 orientation;
};

#endif // GAMEOBJECT_HPP
