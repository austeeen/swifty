#include "scene.hpp"
#include "layers.hpp"


ImageResource::ImageResource(const tb::Image& rsrc)
{
    img_texture.loadFromFile("res/" + std::string(rsrc.source));
    render_states = new sf::RenderStates(&img_texture);
}

ImageResource::~ImageResource()
{
    delete render_states;
    render_states = nullptr;
}

Scene::Scene(GameManager* mngr, const std::string& tmx_fp):
    game_manager(mngr),
    tmx(new tb::Tmx())
{
    for (auto& [name, tileset]: tmx->tilesets) {
        img_srcs[tileset.name] = new ImageResource(tileset.image);
    }

    tb::load<tb::Tmx>(tmx_fp, *tmx);
    for (tb::Layer& lyr : tmx->layers) {
        if (lyr.name == "background") {
            img_layers.push_back(new ImageLayer(this, dynamic_cast<tb::TileLayer&>(lyr)));
        }  else if (lyr.name == "static") {
            obj_layers.push_back(new BoundaryLayer(this, dynamic_cast<tb::ObjectLayer&>(lyr)));
        } else if (lyr.name == "dynamic") {
            obj_layers.push_back(new PlatformLayer(this, dynamic_cast<tb::ObjectLayer&>(lyr)));
        } else if (lyr.name == "terrain") {
            // work out terrain stuff
        } else if (lyr.name == "locations") {
            obj_layers.push_back(new GameObjectLayer(this, dynamic_cast<tb::ObjectLayer&>(lyr)));
        }
    }
}

Scene::~Scene()
{
    for (auto lyr : img_layers) {
        delete lyr;
    }
    img_layers.clear();

    for (auto lyr : obj_layers) {
        delete lyr;
    }
    obj_layers.clear();

    for (auto [id, src] : img_srcs) {
        delete src;
    }
    img_srcs.clear();

    delete tmx;
    tmx = nullptr;
}

void Scene::build()
{
    for (auto lyr : img_layers) {
        lyr->build();
    }
    for (auto lyr : obj_layers) {
        lyr->build();
    }
}

void Scene::setUp()
{
    for (auto lyr : obj_layers) {
        lyr->setUp();
    }

    // todo - set all game object initial positions

    // todo - set colliders in collision_system
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
        case sf::Keyboard::Escape: { game_manager->closeWindow(); break; }

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
            for (auto& lyr : obj_layers) {
                lyr->toggleDisplay();
            }
            break;
        }
        default: { break; }
    }
}

void Scene::update(const float dt)
{
    for (auto lyr : obj_layers) {
        lyr->update(dt);
    }
    collision_system.checkCollisions();
}

void Scene::lateUpdate()
{
    for (auto lyr : obj_layers) {
        lyr->lateUpdate();
    }
}

void Scene::render(sf::RenderWindow &window)
{
    for (auto lyr : img_layers) {
        lyr->render(window);
    }
    for (auto lyr : obj_layers) {
        lyr->render(window);
    }
}

const sf::Vector2f Scene::getViewportCenter() const
{
    return player->cmpnt<RigidBody>()->getPosition();
}
