#ifndef GAME_HPP
#define GAME_HPP

#include "common.hpp"
#include "data.hpp"
#include "camera.hpp"
#include "objects/all.hpp"
#include "tiled/all.hpp"
#include "sys_collision.hpp"
#include "io/devices.hpp"
#include "utils/benchmark.hpp"


#define MAX_FRAME_DT 0.025

class Game
{
public:
    Game(const int fps, const bool rects_on, const bool wait_per_frame);
    void init();
    void setUp();
    void update();
    void lateupdate();
    void render();
    void exit();
    bool isRunning() const;

private:
    void sleep(const float sec);
    void waitPerFrame();

    void inputUpdate();
    void eventUpdate();
    void gameUpdate();
    void lateUpdate();

    void resetPlayer();

    // args
    const int fps;
    const bool rects_on;
    bool wait_per_frame;
    
    sf::Clock frame_clock;
    float dt;
    Clock fclock;
    sf::RenderWindow window;
    Camera camera;
    InputDevice *io_device;
    std::shared_ptr<TileMap> tile_map;
    std::shared_ptr<Player> player;
    std::vector<std::shared_ptr<AiObject>> enemies;
    std::vector<std::shared_ptr<MovingPlatform>> platforms;
    std::vector<std::shared_ptr<Boundary>> boundaries;
    CollisionSystem collision_system;
};

#endif // GAME_HPP
