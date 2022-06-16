#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include "common.hpp"
#include "assets.hpp"
#include "typedef.hpp"
#include "c_base.hpp"
#include "c_sprite.hpp"
#include "c_rigid_body.hpp"
#include "c_animator.hpp"

class GameObject
{
public:
    GameObject(const GameObjectAsset ast);
    void setUp();
    void update(const float dt);
    void lateUpdate();
    void render(sf::RenderWindow &window);
    void jump();
    void terminateJump();
    void moving(const int dir);
    void stop(const int dir);
    void increase(const BodyPhysics cf);
    void decrease(const BodyPhysics cf);
    void toggleRects();
    void onColliding(const COLLIDER::group grp, const ColliderType type, const sf::Vector2f& offset);

    const GameObjectAsset& getAsset() const;
    const sf::Vector2f getPosition() const;
    const sf::Vector2i getSize() const;
    const std::vector<CollisionRect>& getRects() const;
    const COLLIDER::group getColliderGroup() const;

    template <typename T> std::shared_ptr<T> cmpnt() const {
        if (cmpts.count(typeid(T)) == 0)
            return nullptr;
        return std::dynamic_pointer_cast<T>(cmpts.at(typeid(T)));
    }

protected:
    COLLIDER::group col_group;
    std::map<std::type_index, std::shared_ptr<Component>> cmpts;
    GameObjectAsset ast;
};

/**************************************************************************************************/

class Boundary
{
public:
    Boundary(const sf::IntRect rect);
    Boundary(const sf::IntRect rect, const sf::Color c);
    void render(sf::RenderWindow &window);
    const sf::Vector2f getPosition() const;
    const sf::Vector2f getSize() const;
    const sf::FloatRect getRect() const;
    const COLLIDER::group getColliderGroup() const;

private:
    COLLIDER::group col_group;
    sf::RectangleShape shape;
    sf::IntRect rect;
    sf::Color color;
};


#endif // GAMEOBJECT_HPP
