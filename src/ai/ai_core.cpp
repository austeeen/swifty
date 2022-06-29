#include "ai_core.hpp"

ConditionalNode::ConditionalNode(Condition cond, Node* pass, Node* fail):
    condition(cond), pass(pass), fail(fail)
{}
Node* ConditionalNode::exec(AiObject* obj)
{
    if ((obj->*condition)()) {
        return pass;
    } else {
        return fail;
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
