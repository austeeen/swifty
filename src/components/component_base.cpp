#include "component_base.hpp"
#include "../objects/game_object.hpp"
#include "../objects/ai_object.hpp"

Component::Component(GameObject* obj): obj(obj)
{}
Component::Component(AiObject* obj): obj(obj)
{}
void Component::build()
{}
void Component::setUp()
{}
void Component::update(const float dt)
{}
void Component::render(sf::RenderWindow &window)
{}
