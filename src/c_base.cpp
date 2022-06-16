#include "c_base.hpp"
#include "game_object.hpp"

Component::Component(GameObject* obj): obj(obj)
{}
void Component::build()
{}
void Component::setUp()
{}
void Component::update(const float dt)
{}
void Component::render(sf::RenderWindow &window)
{}
