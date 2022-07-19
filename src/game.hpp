#ifndef GAME_HPP
#define GAME_HPP

#include "common.hpp"
#include "data.hpp"
#include "camera.hpp"
#include "objects/all.hpp"
#include "scenes/scene.hpp"
#include "sys_collision.hpp"
#include "io/devices.hpp"
#include "utils/benchmark.hpp"

class Game
{
public:
    Game();
    ~Game();
    void build();
    void setUp();
    void update();
    void lateupdate();
    void render();
    void exit();
    bool isRunning() const;

private:
    void sleep(const float sec);
    void inputUpdate();
    void eventUpdate();
    void gameUpdate();
    void lateUpdate();

    sf::Clock frame_clock;
    float dt;
    Clock fclock;
    sf::RenderWindow window;
    Camera camera;
    InputDevice *io_device;

    tb::ResourceTable rsrc_tbl;
    std::map<std::string, Scene*> scene_table;
    Scene *active_scene;
};

#endif // GAME_HPP
