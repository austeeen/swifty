#ifndef AI_CORE_HPP
#define AI_CORE_HPP

#include "../common.hpp"

class AiObject;

typedef bool(AiObject::*Condition)() const;
typedef void(AiObject::*Action)();

struct Node {
    virtual ~Node() {};
    virtual Node* exec(AiObject* obj) =0;
};

struct ConditionalNode: public Node
{
    ConditionalNode(Condition cond);
    ~ConditionalNode();
    Node* exec(AiObject* obj) override;

    Condition condition;
    std::shared_ptr<Node> pass;
    std::shared_ptr<Node> fail;
};

struct ActionNode:  public Node
{
    ActionNode(Action act);
    ~ActionNode() {};
    Node* exec(AiObject* obj) override;

    Action action;
};

typedef std::shared_ptr<Node>            NodePtr;
typedef std::shared_ptr<ActionNode>      ActionPtr;
typedef std::shared_ptr<ConditionalNode> ConditionPtr;

#endif // AI_CORE_HPP
