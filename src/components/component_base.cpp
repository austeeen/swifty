#include "component_base.hpp"
#include "../objects/player.hpp"

Component::Component(Player* obj): obj(obj)
{}
void Component::build()
{}
void Component::setUp()
{}
void Component::update(const float dt)
{}
void Component::render(sf::RenderWindow &window)
{}
