#ifndef CMP_AI_BEHAVIOR_HPP
#define CMP_AI_BEHAVIOR_HPP

#include "component_base.hpp"


struct ActionNode {
    ActionNode();
    virtual void enter(GameObject* obj) = 0;
    virtual void exit(GameObject* obj) = 0;
    virtual bool execute(GameObject* obj) = 0;
    ActionNode* pass;
    ActionNode* fail;
};

struct MoveToRect: public ActionNode
{
    MoveToRect(const sf::FloatRect& dest);
    void enter(GameObject* obj) override;
    void exit(GameObject* obj) override;
    bool execute(GameObject* obj) override;
    sf::FloatRect m_dest;
};

struct BehaviorTree {
    BehaviorTree();
    ActionNode* root;
};

class AiBehavior: public Component
{
public:
    AiBehavior(GameObject* obj);
    void build() override;
    void setUp() override;
    void update(const float dt) override;
    void render(sf::RenderWindow &window) override;

private:
    BehaviorTree* m_tree;
};

#endif // CMP_AI_BEHAVIOR_HPP
