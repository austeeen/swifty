#ifndef OBJ_PLAYER_HPP
#define OBJ_PLAYER_HPP

#include "game_object.hpp"
#include "assets.hpp"
#include "c_base.hpp"
#include "c_sprite.hpp"
#include "c_rigid_body.hpp"
#include "c_animator.hpp"


class Player: public GameObject
{
public:
    Player(const GameObjectAsset ast);
    void setUp() override;
    void update(const float dt) override;
    void lateUpdate() override;
    void render(sf::RenderWindow &window) override;

    void move(const Dir4);
    void stop(const Dir4);
    void jump();
    void terminateJump();

    void increase(const BodyPhysics cf);
    void decrease(const BodyPhysics cf);
    void toggleRects();

    const GameObjectAsset& getAsset() const;
    const sf::Vector2f getPosition() const override;
    const sf::Vector2i getSize() const override;
    const std::vector<CollisionRect>& getRects() const;

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


#endif // OBJ_PLAYER_HPP
