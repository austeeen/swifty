#ifndef OBJ_PLAYER_HPP
#define OBJ_PLAYER_HPP

#include "game_object.hpp"
#include "../assets.hpp"
#include "../components/all.hpp"


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

    void increase(const PhysicsCoeffs::AsEnum cf);
    void decrease(const PhysicsCoeffs::AsEnum cf);
    void toggleRects();

    const GameObjectAsset& getAsset() const;
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
