#ifndef GAME_HPP
#define GAME_HPP

#include "common.hpp"
#include "data.hpp"
#include "camera.hpp"
#include "objects/all.hpp"
#include "tiled/all.hpp"
#include "sys_collision.hpp"
#include "io/devices.hpp"

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
    void inputUpdate();
    void eventUpdate();
    void gameUpdate();
    void lateUpdate();

    sf::Clock frame_clock;
    float dt;

    sf::RenderWindow window;
    Camera camera;
    InputDevice *io_device;
    std::shared_ptr<TileMap> tile_map;
    std::shared_ptr<Player> player;
    std::vector<std::shared_ptr<MovingPlatform>> platforms;
    std::vector<std::shared_ptr<Boundary>> boundaries;
    CollisionSystem collision_system;
};

#endif // GAME_HPP
