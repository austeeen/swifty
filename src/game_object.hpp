#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include "common.hpp"
#include "assets.hpp"
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

    void move(const Dir4);
    void stop(const Dir4);
    void jump();
    void terminateJump();

    void increase(const BodyPhysics cf);
    void decrease(const BodyPhysics cf);
    void toggleRects();

    const GameObjectAsset& getAsset() const;
    const sf::Vector2f getPosition() const;
    const sf::Vector2i getSize() const;
    const std::vector<CollisionRect>& getRects() const;
    const CollisionGroup getColliderGroup() const;

    template <typename T> std::shared_ptr<T> cmpnt() const {
        if (cmpts.count(typeid(T)) == 0)
            return nullptr;
        return std::dynamic_pointer_cast<T>(cmpts.at(typeid(T)));
    }

protected:
    // std::map<const ObjectState, std::unique_ptr<StateBase>> states;
    ObjectState cur_state;

    CollisionGroup col_group;
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
    const CollisionGroup getColliderGroup() const;

private:
    CollisionGroup col_group;
    sf::IntRect rect;
    sf::RectangleShape shape;
    sf::Color color;
};


#endif // GAMEOBJECT_HPP
