#include "game.hpp"

Game::Game(const int fps, const bool rects_on, const bool wait_per_frame):
    fps(fps),
    rects_on(rects_on),
    wait_per_frame(wait_per_frame),
    window(sf::VideoMode(WINDOW::width, WINDOW::height), WINDOW::title, WINDOW::style),
    camera(CAMERA::view_rect)
{
    window.setKeyRepeatEnabled(false);
    window.setFramerateLimit(fps);
    window.setVerticalSyncEnabled(true);

    player = std::make_shared<Player>(GameObjectAsset(std::make_shared<TileObject>("res/cat_new.tsx")));

    enemies.push_back(
        std::make_shared<AiObject>(GameObjectAsset(std::make_shared<TileObject>("res/spider.tsx")))
    );

    tile_map = std::make_shared<TileMap>("res/new_basic_level.tmx");

    tile_map->build();
    for (auto& object_group : tile_map->object_groups) {
        for (auto& rect : object_group->objects) {
            boundaries.push_back(std::make_shared<Boundary>(rect));
        }
    }
    for (auto& dyn_object_group : tile_map->dyn_object_groups) {
        for (auto& [name, dyn_obj] : dyn_object_group->objects) {
            platforms.push_back(std::make_shared<MovingPlatform>(PlatformObjectAsset(dyn_obj)));
        }
    }
}
void Game::setUp()
{
    std::vector<int> cons;
    if (joy::connected_joys(cons)) {
        out::msg("Game::setUp", "%d connected controller(s)", (int) cons.size());
        io_device = new Joystick(cons);
    }
    else {
        io_device = new Keyboard();
    }

    player->build();
    for (auto& enm : enemies) {
        out::msg("Game::setUp", "building: %s", enm->getName().c_str());
        enm->build();
    }

    player->setUp();
    for (auto& plt : platforms) {
        plt->setUp();
    }
    for (auto& enm : enemies) {
        out::msg("Game::setUp", "setting up: %s", enm->getName().c_str());
        enm->setUp();
    }

    // todo - will make this more robust eventually
    const sf::IntRect player_start = tile_map->spawn_locations->to_spawn["player"];
    player->setStartPosition(player_start.getPosition());

    // todo - will make this more robust eventually
    const sf::IntRect spider_start = tile_map->spawn_locations->to_spawn["spider"];
    enemies[0]->setStartPosition(spider_start.getPosition());
    enemies[0]->setAiZone(tile_map->ai_zones->all_zones["spider"]);

    collision_system.add(player);
    for (auto& bnd : boundaries) {
        collision_system.add(bnd);
    }
    for (auto& plt : platforms) {
        collision_system.add(plt);
    }
    for (auto& enm : enemies) {
        collision_system.add(enm);
    }

    camera.setCenter(player->cmpnt<RigidBody>()->getPosition());
    camera.update(window.getSize());

    fclock.restart();
    fclock.start();

    dt = frame_clock.restart().asSeconds();

    // Turn on all rects
    if (rects_on) {
        player->toggleRects(true);
        for (auto& plt : platforms) {
            plt->toggleDisplay(true);
        }
        for (auto& enm : enemies) {
            enm->toggleRects(true);
        }
    }
}
void Game::update()
{
    dt = frame_clock.restart().asSeconds();
    inputUpdate();
    eventUpdate();
    gameUpdate();
    fclock.tick();

    if (wait_per_frame) {
        waitPerFrame();
    }
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
                if (event.key.alt) {
                    switch (event.key.code) {
                        default: { break; }

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
                    }
                } else {
                    switch (event.key.code) {
                        case sf::Keyboard::Escape: { window.close(); break; }
                        case sf::Keyboard::Tab: {
                            resetPlayer();
                            break;
                        }
                        case sf::Keyboard::R: {
                            player->toggleRects();
                            for (auto& plt : platforms) {
                                plt->toggleDisplay();
                            }
                            for (auto& enm : enemies) {
                                enm->toggleRects();
                            }
                            break;
                        }
                        case sf::Keyboard::Tilde: {
                            wait_per_frame = true;
                            break;
                        }
                        default: { break; }
                    }
                }
                break;
            }
            default: { break; }
        }
    }
}
void Game::gameUpdate()
{

    // Cap dt between frames to 10 ms max.
    // This should remedy issues where the game window hangs for some time and the update method
    // tries to process using a super high dt.
    if (dt > MAX_FRAME_DT) {
        float og_dt = dt;
        dt = MAX_FRAME_DT;
        out::debug("Game::gameUpdate", "DT: %f -> %f (sec)", og_dt, dt);
    }

    player->update(dt);
    for (auto& enm : enemies) {
        enm->update(dt);
    }
    for (auto& plt : platforms) {
        plt->update(dt);
    }

    collision_system.checkCollisions();

    player->lateUpdate();
    for (auto& enm : enemies) {
        enm->lateUpdate();
    }
    for (auto& plt : platforms) {
        plt->lateUpdate();
    }

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
    for (auto& enm : enemies) {
        enm->render(window);
    }
    for (auto& plt : platforms) {
        plt->render(window);
    }
    window.display();
}
void Game::exit()
{
    fclock.stop();
    out::msg("Game::exit", "run time: %d", fclock.num_ticks);
    out::msg("Game::exit", "  frames: %f", fclock.duration.count());
    out::msg("Game::exit", "     fps: %f", fclock.num_ticks / fclock.duration.count());
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
void Game::waitPerFrame()
{
    bool wait = true;
    out::msg("Press 'n' for next frame...");
    while (wait) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) { 
                window.close();
            }
            else if (event.type == sf::Event::Resized) {
                camera.update(sf::Vector2u(event.size.width, event.size.height));
            }
            else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::N) {
                    wait = false;
                }
                else if (event.key.code == sf::Keyboard::Tilde) {
                    wait_per_frame = false;
                }
                else if (event.key.code == sf::Keyboard::R) {
                    player->toggleRects();
                    for (auto& plt : platforms) {
                        plt->toggleDisplay();
                    }
                    for (auto& enm : enemies) {
                        enm->toggleRects();
                    }
                }
                else if (event.key.code == sf::Keyboard::Escape) { 
                    window.close();
                }
            }
        }
    }
}

bool Game::isRunning() const
{
    return window.isOpen();
}

void Game::resetPlayer()
{
    player->stopAll();
    player->resetPosition();
}
