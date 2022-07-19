#include "scene.hpp"

ImageResource::ImageResource(tb::Image& rsrc)
{
    img_texture.loadFromFile("res/" + rsrc.source);
    render_states = new sf::RenderStates(&img_texture);
}

Scene::Scene(const char* tmx_fp):
    tmx(new tb::Tmx())
{
    for (auto& [name, tileset]: tmx->tilesets) {
        img_srcs[tileset.name] = new ImageResource(tileset.image)
    }

    load<tb::Tmx>(tmx_fp, *tmx);
    for (tb::Layer& lyr : tmx->layers) {
            if (lyr.name == "background") {
                layers.push_back(new ImageLayer(this, dynamic_cast<tb::TileLayer>(lyr)));
            }  else if (lyr.name == "static") {
                layers.push_back(new StaticLayer(this, dynamic_cast<tb::ObjectLayer>(lyr)));
            } else if (lyr.name == "dynamic") {
                layers.push_back(new SceneObjects(this, dynamic_cast<tb::ObjectLayer>(lyr)));
            } else if (lyr.name == "terrain") {
                // work out terrain stuff
            } else if (lyr.name == "locations") {
                layers.push_back(new GameObjects(this, dynamic_cast<tb::ObjectLayer>(lyr)));
            }
        }
    }
}

Scene::~Scene()
{
    for (auto lyr : layers) {
        delete lyr;
    }
    layers.clear();

    for (auto src : img_srcs) {
        delete src;
    }
    img_srcs.clear();

    delete tmx;
    tmx = nullptr;
}

void Scene::build()
{
    for (auto lyr : layers) {
        lyr->build();
    }
}

void Scene::setUp()
{
    for (auto lyr : layers) {
        lyr->setUp();
    }

    // todo - set all game object initial positions

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


}

void Scene::onUserInput(InputDevice *io_device)
{
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

void Scene::onUserEvent(sf::Event &event)
{
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
        default: { break; }
    }
}

void Scene::update(const float dt)
{
    for (auto lyr : layers) {
        lyr->update(dt);
    }

    collision_system.checkCollisions();
}

void Scene::lateUpdate()
{
    for (auto lyr : layers) {
        lyr->lateupdate();
    }
}

void Scene::render(sf::RenderWindow &window)
{
    for (auto lyr : layers) {
        lyr->render(window);
    }
}

const sf::Vector2f& Scene::getViewportCenter() const
{
    return player->cmpnt<RigidBody>()->getPosition();
}
