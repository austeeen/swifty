#include "ai_core.hpp"

ConditionalNode::ConditionalNode(Condition cond):
    condition(cond), pass(nullptr), fail(nullptr)
{}
ConditionalNode::~ConditionalNode()
{
    pass = nullptr;
    fail = nullptr;
}
Node* ConditionalNode::exec(AiObject* obj)
{
    if ((obj->*condition)()) {
        return pass.get();
    } else {
        return fail.get();
    }
}

/**************************************************************************************************/

ActionNode::ActionNode(Action act):
    action(act)
{}
Node* ActionNode::exec(AiObject* obj)
{
   (obj->*action)();
   return nullptr;
}
