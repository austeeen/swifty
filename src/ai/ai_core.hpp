#ifndef AI_CORE_HPP
#define AI_CORE_HPP

#include "../common.hpp"

class AiObject;

typedef bool (AiObject::*Condition)();
typedef void (AiObject::*Action)();

struct Node {
    virtual Node* exec(AiObject* obj) =0;
};

struct ConditionalNode: public Node
{
    ConditionalNode(Condition cond, Node* pass, Node* fail);
    Node* exec(AiObject* obj) override;

    Condition condition;
    Node* pass;
    Node* fail;
};

struct ActionNode:  public Node
{
    ActionNode(Action act);
    Node* exec(AiObject* obj) override;

    Action action;
};



#endif // AI_CORE_HPP
