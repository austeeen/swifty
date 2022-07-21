#ifndef GAME_MANAGER_HPP
#define GAME_MANAGER_HPP

#include "common.hpp"
#include "data.hpp"
#include "camera.hpp"
#include "io/devices.hpp"
#include "utils/benchmark.hpp"

class Scene;

class GameManager
{
public:
    GameManager();
    ~GameManager();
    void build();
    void setUp();
    void update();
    void lateupdate();
    void render();

    void exit();
    void closeWindow();
    bool isRunning() const;

private:
    void inputUpdate();
    void eventUpdate();
    void gameUpdate();
    void lateUpdate();

    void sleep(const float sec);

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

#endif // GAME_MANAGER_HPP
