#include "ai_controller.hpp"

AiController::AiController(AiObject* obj):
    Component(obj)
{
    m_state_tbl[AiState::Type::wandering] = new Wandering(obj);
    m_state_tbl[AiState::Type::stalking] = new Stalking(obj);
    m_state_tbl[AiState::Type::returning] = new Returning(obj);
}
void AiController::build()
{
    // todo create state decision trees
    // state_tbl[state_type]->setDecisionRoot(root)
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
