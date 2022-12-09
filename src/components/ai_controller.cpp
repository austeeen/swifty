#include "ai_controller.hpp"
#include "../objects/ai_object.hpp"

AiController::AiController(AiObject* obj):
    Component(obj), m_obj(obj)
{
    m_state_tbl[AiState::Type::wandering] = new Wandering(obj);
    m_state_tbl[AiState::Type::stalking] = new Stalking(obj);
    m_state_tbl[AiState::Type::returning] = new Returning(obj);
}
AiController::~AiController()
{
    for (auto& n : m_allnodes) {
        delete n;
    }
    m_allnodes.clear();

    for (auto& [state_type, state] : m_state_tbl) {
        delete state;
    }
    m_state_tbl.clear();
}
void AiController::build()
{
    // todo create state decision trees
    ActionNode* a0 = new ActionNode(&AiObject::setPathFromZone);
    ActionNode* a1 = new ActionNode(&AiObject::clearDestination);
    ActionNode* a2 = new ActionNode(&AiObject::noAction);
    ActionNode* a3 = new ActionNode(&AiObject::attackTarget);
    ActionNode* a4 = new ActionNode(&AiObject::redrawPath);
    ActionNode* a5 = new ActionNode(&AiObject::setPathToHome);

    // wandering tree
    ConditionalNode* w_c0 = new ConditionalNode(&AiObject::hasDestination);
    ConditionalNode* w_c1 = new ConditionalNode(&AiObject::closeToDestination);
    ConditionalNode* w_c2 = new ConditionalNode(&AiObject::isStuck);
    w_c0->pass = w_c1;
    w_c0->fail = a0;

    w_c1->pass = a1;
    w_c1->fail = w_c2;

    w_c2->pass = a1;
    w_c2->fail = a2;
    m_state_tbl[AiState::Type::wandering]->setRoot(w_c0);

    // stalking tree
    ConditionalNode* s_c0 = new ConditionalNode(&AiObject::closeToTarget);
    ConditionalNode* s_c1 = new ConditionalNode(&AiObject::isStuck);
    s_c0->pass = a3;
    s_c0->fail = s_c1;

    s_c1->pass = a4;
    s_c1->fail = a2;
    m_state_tbl[AiState::Type::stalking]->setRoot(s_c0);

    // returning tree
    ConditionalNode* r_c0 = new ConditionalNode(&AiObject::hasDestination);
    ConditionalNode* r_c1 = new ConditionalNode(&AiObject::isStuck);
    r_c0->pass = r_c1;
    r_c0->fail = a5;

    s_c1->pass = a4;
    s_c1->fail = a2;
    m_state_tbl[AiState::Type::returning]->setRoot(r_c0);

    m_allnodes.push_back(a0);
    m_allnodes.push_back(a1);
    m_allnodes.push_back(a2);
    m_allnodes.push_back(a3);
    m_allnodes.push_back(a4);
    m_allnodes.push_back(a5);

    m_allnodes.push_back(w_c0);
    m_allnodes.push_back(w_c1);
    m_allnodes.push_back(w_c2);
    m_allnodes.push_back(s_c0);
    m_allnodes.push_back(s_c1);
    m_allnodes.push_back(r_c0);
    m_allnodes.push_back(r_c1);

    m_state = AiState::Type::wandering;

}
void AiController::setUp()
{

}
void AiController::update(const float dt)
{
    m_state_tbl[m_state]->observe();
    m_state_tbl[m_state]->processDecision();

    if (m_obj_state == ObjectState::idle) {
        stuck_dt += dt;
    } else {
        stuck_dt = 0.f;
    }
}
void AiController::setState(ObjectState s)
{
    m_obj_state = s;
}
const bool AiController::stuckTimedout() const
{
    return stuck_dt > stuck_timeout;
}
