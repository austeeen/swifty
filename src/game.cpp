#include "game.hpp"

Game::Game():
    window(sf::VideoMode(WINDOW::width, WINDOW::height), WINDOW::title, WINDOW::style),
    camera(CAMERA::view_rect)
{
    window.setKeyRepeatEnabled(false);
    // window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);

    tb::search("res/", rsrc_tbl);

    for (auto& [name, tmx_path] : rsrc_tbl.at(FileType::Tmx)) {
        scene_table[name] = new Scene(tmx_path);
    }
}
Game::~Game()
{
    for (auto& [name, scene] : scene_table) {
        delete scene;
    }
    scene_table.clear();
}
void Game::build()
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
void Game::setUp()
{
    active_scene->setUp();

    camera.setCenter(active_scene->getViewportCenter());
    camera.update(window.getSize());

    fclock.restart();
    fclock.start();

    dt = frame_clock.restart().asSeconds();
}
void Game::update()
{
    dt = frame_clock.restart().asSeconds();
    inputUpdate();
    eventUpdate();
    gameUpdate();
    fclock.tick();
}
void Game::inputUpdate()
{
    io_device->update();
    active_scene->inputUpdate(io_device);
}
void Game::eventUpdate()
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
                active_scene->eventUpdate(event);
            }
            default: { break; }
        }
    }
}
void Game::gameUpdate()
{
    active_scene->update(dt);
    active_scene->lateUpdate();

    camera.setCenter(active_scene->getViewportCenter());
    camera.applyView(window);
}
void Game::render()
{
    window.clear(sf::Color::Black);
    active_scene->render(window);
    window.display();
}
void Game::exit()
{
    fclock.stop();
    std::cout << "num frames: " << fclock.num_ticks << "\n";
    std::cout << "run time: " << fclock.duration.count() << "\n";
    std::cout << "fps: " << fclock.num_ticks / fclock.duration.count() << "\n";
}
void Game::sleep(const float sec)
{
    sf::Clock wait_clock;
    wait_clock.restart().asSeconds();
    float wait_dt = 0.0;
    while (wait_dt < 0.1f) {
        wait_dt += wait_clock.restart().asSeconds();
    }
    frame_clock.restart().asSeconds();
}
bool Game::isRunning() const
{
    return window.isOpen();
}
