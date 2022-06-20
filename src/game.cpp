#include "game.hpp"

Game::Game():
window(sf::VideoMode(WINDOW::width, WINDOW::height), WINDOW::title, WINDOW::style),
camera(CAMERA::view_rect),
tile_map(std::make_shared<TileMap>("res/new_basic_level.tmx"))
{
    window.setKeyRepeatEnabled(false);

    TileObject cat_res("res/cat.tsx");
    GameObjectAsset cat_ast(cat_res);
    player = std::make_shared<Player>(cat_ast);

    tile_map->build();
    for (auto& object_group : tile_map->object_groups) {
        for (auto& [id, rect] : object_group->objects) {
            boundaries.push_back(std::make_shared<Boundary>(rect));
        }
    }
}
void Game::setUp()
{
    std::vector<int> cons;
    if (joy::connected_joys(cons)) {
        printf("%d connected controller(s)", (int) cons.size());
        io_device = new Joystick(cons);
    }
    else {
        io_device = new Keyboard();
    }

    player->setUp();
    collision_system.add(player);
    for (auto& bnd : boundaries) {
        collision_system.add(bnd);
    }
    camera.setCenter(player->cmpnt<RigidBody>()->getPosition());
    camera.update(window.getSize());
    dt = frame_clock.restart().asSeconds();
}
void Game::update()
{
    dt = frame_clock.restart().asSeconds();
    inputUpdate();
    eventUpdate();
    gameUpdate();
    lateUpdate();
}
void Game::inputUpdate()
{
    io_device->update();

    io::binding b = io_device->get(io::left);
    if (b == io::pressed_s) {
        player->move(Dir4::left);
    } else if (b == io::released_s) {
        player->stop(Dir4::left);
    }

    b = io_device->get(io::right);
    if (b == io::pressed_s) {
        player->move(Dir4::right);
    } else if (b == io::released_s) {
        player->stop(Dir4::right);
    }

    b = io_device->get(io::jump);
    if (b == io::pressed_s) {
        player->jump();
    } else if (b == io::released_s) {
        player->terminateJump();
    }
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
                switch (event.key.code) {
                    case sf::Keyboard::Escape: { window.close(); break; }

                    case sf::Keyboard::A: { player->increase(PhysicsCoeffs::AsEnum::mass); break; }
                    case sf::Keyboard::Z: { player->decrease(PhysicsCoeffs::AsEnum::mass); break; }

                    case sf::Keyboard::S: { player->increase(PhysicsCoeffs::AsEnum::speed); break; }
                    case sf::Keyboard::X: { player->decrease(PhysicsCoeffs::AsEnum::speed); break; }

                    case sf::Keyboard::D: { player->increase(PhysicsCoeffs::AsEnum::maxvel); break; }
                    case sf::Keyboard::C: { player->decrease(PhysicsCoeffs::AsEnum::maxvel); break; }

                    case sf::Keyboard::F: { player->increase(PhysicsCoeffs::AsEnum::jump); break; }
                    case sf::Keyboard::V: { player->decrease(PhysicsCoeffs::AsEnum::jump); break; }

                    case sf::Keyboard::H: { player->increase(PhysicsCoeffs::AsEnum::damping); break; }
                    case sf::Keyboard::N: { player->decrease(PhysicsCoeffs::AsEnum::damping); break; }

                    case sf::Keyboard::J: { player->increase(PhysicsCoeffs::AsEnum::gravity); break; }
                    case sf::Keyboard::M: { player->decrease(PhysicsCoeffs::AsEnum::gravity); break; }
                    case sf::Keyboard::R: { player->toggleRects(); break; }
                    default: { break; }
                }
                break;
            }
            default: { break; }
        }
    }
}
void Game::gameUpdate()
{
    player->update(dt);
    collision_system.checkCollisions();
}
void Game::lateUpdate()
{
    player->lateUpdate();
    camera.setCenter(player->cmpnt<RigidBody>()->getPosition());
    camera.applyView(window);
}
void Game::render()
{
    window.clear(sf::Color::Black);
    for (auto& tile_layer : tile_map->tile_layers) {
        window.draw(sf::Sprite(tile_layer->render_texture->getTexture()));
    }
    player->render(window);
    window.display();
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
