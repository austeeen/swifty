#include "ai_controller.hpp"
#include "../objects/ai_object.hpp"

AiController::AiController(AiObject* obj):
    Component(obj), m_obj(obj)
{
    m_state_tbl[AiState::Type::wandering] = new Wandering(obj);
    m_state_tbl[AiState::Type::stalking] = new Stalking(obj);
    m_state_tbl[AiState::Type::returning] = new Returning(obj);
}
void AiController::build()
{
    // todo create state decision trees
    // state_tbl[state_type]->setDecisionRoot(root)

    ActionNode* a0 = new ActionNode(&AiObject::newDestination);
    ActionNode* a1 = new ActionNode(&AiObject::clearDestination);
    ActionNode* a2 = new ActionNode(&AiObject::noAction);

    // wandering tree
    ConditionalNode* c0 = new ConditionalNode(&AiObject::targetDetected);
    ConditionalNode* c1 = new ConditionalNode(&AiObject::closeToDestination);
    ConditionalNode* c2 = new ConditionalNode(&AiObject::isStuck);
    c0->pass = c1;
    c0->fail = a0;

    c1->pass = a1;
    c1->fail = c2;

    c2->pass = a1;
    c2->fail = a2;
    m_state_tbl[AiState::Type::wandering]->setRoot(c0);

    // stalking tree


    // returning tree

}
void AiController::setUp()
{

}
void AiController::update(const float dt)
{
    // todo :
    // ObjectState cur_state = [some state calculated based on body/physics/pathing?]
    // do ai state stuff [observe, processDecision]
    // check for being 'stuck'?
        // may just check if cur_state == idle?
        // may involve pathing2d, rigid body, physics 2d, etc not sure yet.
        // update stuck_dt
    // else
        // clear stuck_dt
}
const bool AiController::stuckTimedout() const
{
    return stuck_dt > stuck_timeout;
}
