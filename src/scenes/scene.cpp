#include "scene.hpp"

Scene::Scene(const char* tmx_fp):
    tmx(new tb::Tmx())
{
    load<tb::Tmx>(tmx_fp, *tmx);
    for (tb::Layer& lyr : tmx->layers) {
            if (lyr.name == "background") {
                layers.push_back(new ImageLayer(this, dynamic_cast<tb::TileLayer>(lyr)));
            } else if (lyr.name == "dynamic") {
                layers.push_back(new SceneLayer(this, dynamic_cast<tb::ObjectLayer>(lyr)));
            } else if (lyr.name == "static") {
                layers.push_back(new StaticLayer(this, dynamic_cast<tb::ObjectLayer>(lyr)));
            } else if (lyr.name == "terrain") {
                // work out terrain stuff
            } else if (lyr.name == "location") {
                layers.push_back(new GameObjects(this, dynamic_cast<tb::ObjectLayer>(lyr)));
            } else if (lyr.name == "zone") {
                // combine this with 'location' as a new type called 'game objects'
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
}

void Scene::update(const float dt)
{
    for (auto lyr : layers) {
        lyr->update(dt);
    }
}

void Scene::lateupdate()
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
