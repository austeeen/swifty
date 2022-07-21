#include "game_manager.hpp"
#include "scenes/scene.hpp"

GameManager::GameManager():
    window(sf::VideoMode(WINDOW::width, WINDOW::height), WINDOW::title, WINDOW::style),
    camera(CAMERA::view_rect)
{
    window.setKeyRepeatEnabled(false);
    // window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);

    tb::search("res/", rsrc_tbl);

    tb::FileMap tmx_files = rsrc_tbl.at(tb::FileType::Tmx);
    for (auto& [name, fp] : tmx_files) {
        scene_table[name] = new Scene(this, fp);
    }
}

GameManager::~GameManager()
{
    for (auto& [name, scene] : scene_table) {
        delete scene;
    }
    scene_table.clear();
}

void GameManager::build()
{
    std::vector<int> cons;
    if (joy::connected_joys(cons)) {
        printf("%d connected controller(s)", (int) cons.size());
        io_device = new Joystick(cons);
    }
    else {
        io_device = new Keyboard();
    }

    active_scene = scene_table.at("new_basic_level");
    active_scene->build();
}

void GameManager::setUp()
{
    active_scene->setUp();

    camera.setCenter(active_scene->getViewportCenter());
    camera.update(window.getSize());

    fclock.restart();
    fclock.start();

    dt = frame_clock.restart().asSeconds();
}

void GameManager::update()
{
    dt = frame_clock.restart().asSeconds();
    inputUpdate();
    eventUpdate();
    gameUpdate();
    fclock.tick();
}

void GameManager::inputUpdate()
{
    io_device->update();
    active_scene->onUserInput(io_device);
}

void GameManager::eventUpdate()
{
    sf::Event event;
    while (window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed: { window.close(); break; }
            case sf::Event::Resized: {
                camera.update(sf::Vector2u(event.size.width, event.size.height));
                break;
            }
            case sf::Event::KeyPressed: {
                active_scene->onUserEvent(event);
            }
            default: { break; }
        }
    }
}

void GameManager::gameUpdate()
{
    active_scene->update(dt);
    active_scene->lateUpdate();

    camera.setCenter(active_scene->getViewportCenter());
    camera.applyView(window);
}

void GameManager::render()
{
    window.clear(sf::Color::Black);
    active_scene->render(window);
    window.display();
}

void GameManager::exit()
{
    fclock.stop();
    std::cout << "num frames: " << fclock.num_ticks << "\n";
    std::cout << "run time: " << fclock.duration.count() << "\n";
    std::cout << "fps: " << fclock.num_ticks / fclock.duration.count() << "\n";
}

void GameManager::closeWindow()
{
    window.close();
}

bool GameManager::isRunning() const
{
    return window.isOpen();
}

void GameManager::sleep(const float sec)
{
    sf::Clock wait_clock;
    wait_clock.restart().asSeconds();
    float wait_dt = 0.0;
    while (wait_dt < 0.1f) {
        wait_dt += wait_clock.restart().asSeconds();
    }
    frame_clock.restart().asSeconds();
}
