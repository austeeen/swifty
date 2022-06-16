#ifndef GAME_HPP
#define GAME_HPP

#include "common.hpp"
#include "data.hpp"
#include "camera.hpp"
#include "game_object.hpp"
#include "sys_collision.hpp"
#include "rsrc_tiled.hpp"

class Game
{
public:
    Game();
    void init();
    void setUp();
    void update();
    void lateupdate();
    void render();
    bool isRunning() const;

private:
    void sleep(const float sec);
    void __inputUpdate();
    void __gameUpdate();
    void __lateUpdate();

    sf::Clock frame_clock;
    float dt;

    sf::RenderWindow window;
    Camera camera;

    std::shared_ptr<TileMap> tile_map;
    std::shared_ptr<GameObject> player;
    std::vector<std::shared_ptr<Boundary>> boundaries;
    CollisionSystem collision_system;
};

#endif // GAME_HPP
