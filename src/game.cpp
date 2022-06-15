#include "game.hpp"

Game::Game():
window(sf::VideoMode(WINDOW::width, WINDOW::height), WINDOW::title, WINDOW::style),
camera(CAMERA::view_rect),
tile_map(std::make_shared<TileMap>("res/new_basic_level.tmx"))
{
    window.setKeyRepeatEnabled(false);

    TileObject cat_res("res/cat.tsx");
    GameObjectAsset cat_ast(cat_res);
    player = std::make_shared<GameObject>(cat_ast);

    tile_map->build();
    for (auto& object_group : tile_map->object_groups) {
        for (auto& [id, rect] : object_group->objects) {
            boundaries.push_back(std::make_shared<Boundary>(rect));
        }
    }
}
void Game::setUp()
{
    player->setUp();
    collision_system.add(player);
    for (auto& bnd : boundaries) {
        collision_system.add(bnd);
    }
    camera.setCenter(player->getPosition());
    camera.update(window.getSize());
    dt = frame_clock.restart().asSeconds();
}
void Game::update()
{
    dt = frame_clock.restart().asSeconds();
    // sleep(0.5f);
    __inputUpdate();
    __gameUpdate();
    __lateUpdate();
}
void Game::__inputUpdate()
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
                    case sf::Keyboard::Q: { window.close(); break; }
                    case sf::Keyboard::Escape: { window.close(); break; }
                    case sf::Keyboard::Space: { player->jump(); break; }
                    case sf::Keyboard::Left: { player->moving(DIR_LEFT); break; }
                    case sf::Keyboard::Right: { player->moving(DIR_RIGHT); break; }

                    case sf::Keyboard::A: { player->increase(BodyPhysics::mass); break; }
                    case sf::Keyboard::Z: { player->decrease(BodyPhysics::mass); break; }

                    case sf::Keyboard::S: { player->increase(BodyPhysics::speed); break; }
                    case sf::Keyboard::X: { player->decrease(BodyPhysics::speed); break; }

                    case sf::Keyboard::D: { player->increase(BodyPhysics::max_x_vel); break; }
                    case sf::Keyboard::C: { player->decrease(BodyPhysics::max_x_vel); break; }

                    case sf::Keyboard::F: { player->increase(BodyPhysics::jump_power); break; }
                    case sf::Keyboard::V: { player->decrease(BodyPhysics::jump_power); break; }

                    case sf::Keyboard::H: { player->increase(BodyPhysics::damping); break; }
                    case sf::Keyboard::N: { player->decrease(BodyPhysics::damping); break; }

                    case sf::Keyboard::J: { player->increase(BodyPhysics::gravity); break; }
                    case sf::Keyboard::M: { player->decrease(BodyPhysics::gravity); break; }
                    default: { break; }
                }
                break;
            }
            case sf::Event::KeyReleased: {
                switch (event.key.code) {
                    case sf::Keyboard::Up: { player->stop(DIR_UP); break; }
                    case sf::Keyboard::Down: { player->stop(DIR_DOWN); break; }
                    case sf::Keyboard::Left: { player->stop(DIR_LEFT); break; }
                    case sf::Keyboard::Right: { player->stop(DIR_RIGHT); break; }
                    case sf::Keyboard::Space: { player->terminateJump(); break; }
                    default: { break; }
                }
                break;
            }
            default: { break; }
        }
    }
}
void Game::__gameUpdate()
{
    player->update(dt);
    physics_system.update(player->cmpnt<RigidBody>(), dt);
}
void Game::__lateUpdate()
{
    collision_system.checkCollisions();
    camera.setCenter(player->getPosition());
    camera.applyView(window);
}
void Game::render()
{
    window.clear(sf::Color::Blue);
    for (auto& tile_layer : tile_map->tile_layers) {
        window.draw(sf::Sprite(tile_layer->render_texture->getTexture()));
    }
    /*
    for (auto& bndry : boundaries) {
        bndry->render(window);
    }
    */
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
