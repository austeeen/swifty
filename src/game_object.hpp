#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include "common.hpp"
#include "components.hpp"
#include "assets.hpp"
#include "typedef.hpp"

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
    void increase(const int cf);
    void decrease(const int cf);
    void onColliding(const COLLIDER::group grp, const sf::Vector2f offset);
    const GameObjectAsset& getAsset() const;
    const sf::Vector2f getPosition() const;
    const sf::Vector2i getSize() const;
    const sf::FloatRect getRect() const;
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

/**************************************************************************************************/

class Background
{
public:
    Background(const std::string img_fp);
    void render(sf::RenderWindow& window);
    void setCenter(const sf::Vector2f center);
    const sf::Vector2f getPosition() const;
    const sf::Vector2f getSize() const;
    const sf::FloatRect getRect() const;

private:
    sf::Texture img_texture;
    sf::Sprite sprite;
};


#endif // GAMEOBJECT_HPP
