#ifndef CMP_AI_BEHAVIOR_HPP
#define CMP_AI_BEHAVIOR_HPP

#include "component_base.hpp"

class AiBehavior: public Component
{
public:
    AiBehavior(KinematicObject* obj);
    void build() override;
    void setUp() override;
    void update(const float dt) override;
    void render(sf::RenderWindow &window) override;

private:
    
};

#endif // CMP_AI_BEHAVIOR_HPP
