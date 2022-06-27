#include "component_base.hpp"
#include "../objects/game_object.hpp"

Component::Component(KinematicObject* obj): obj(obj)
{}
void Component::build()
{}
void Component::setUp()
{}
void Component::update(const float dt)
{}
void Component::render(sf::RenderWindow &window)
{}
