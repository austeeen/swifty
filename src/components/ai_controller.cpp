#include "ai_controller.hpp"
#include "../objects/ai_object.hpp"
#include "../typedefs.hpp"


AiController::AiController(AiObject* obj):
    Component(obj), m_obj(obj)
{
    m_state_tbl[AiState::Type::wandering] = new Wandering(obj);
    m_state_tbl[AiState::Type::stalking] = new Stalking(obj);
    m_state_tbl[AiState::Type::returning] = new Returning(obj);
}

AiController::~AiController()
{
    for (auto& [state_type, state] : m_state_tbl) {
        delete state;
    }
    m_state_tbl.clear();
}

void AiController::build()
{
    // initializing actions to reference
    ActionPtr set_new_path  = std::make_shared<ActionNode>(&AiObject::setPathFromZone);
    ActionPtr clear_dest    = std::make_shared<ActionNode>(&AiObject::clearDestination);
    ActionPtr no_op         = std::make_shared<ActionNode>(&AiObject::noAction);
    ActionPtr attack_target = std::make_shared<ActionNode>(&AiObject::attackTarget);
    ActionPtr redraw_path   = std::make_shared<ActionNode>(&AiObject::redrawPath);
    ActionPtr set_path_home = std::make_shared<ActionNode>(&AiObject::setPathToHome);

    /* Build the WANDERING tree */
    {
        // initializing conditions
        ConditionPtr has_dest      = std::make_shared<ConditionalNode>(&AiObject::hasDestination);
        ConditionPtr close_to_dest = std::make_shared<ConditionalNode>(&AiObject::closeToDestination);
        ConditionPtr is_stuck      = std::make_shared<ConditionalNode>(&AiObject::isStuck);
        
        // associating conditions with actions
        has_dest->pass = close_to_dest;
        has_dest->fail = set_new_path;

        close_to_dest->pass = clear_dest;
        close_to_dest->fail = is_stuck;

        is_stuck->pass = clear_dest;
        is_stuck->fail = no_op;

        // add the wandering tree root to the state table
        m_state_tbl[AiState::Type::wandering]->setRoot(has_dest);
    }
    

    /* Build the STALKING tree */
    {
        // initializing conditions
        ConditionPtr close_to_target = std::make_shared<ConditionalNode>(&AiObject::closeToTarget);
        ConditionPtr is_stuck = std::make_shared<ConditionalNode>(&AiObject::isStuck);

        // associating conditions with actions
        close_to_target->pass = attack_target;
        close_to_target->fail = is_stuck;

        is_stuck->pass = redraw_path;
        is_stuck->fail = no_op;

        // add the stalking tree root to the state table
        m_state_tbl[AiState::Type::stalking]->setRoot(close_to_target);
    }
    
    /* Build the RETURNING tree */
    {
        // initializing conditions
        ConditionPtr has_dest = std::make_shared<ConditionalNode>(&AiObject::hasDestination);
        ConditionPtr is_stuck = std::make_shared<ConditionalNode>(&AiObject::isStuck);

        // associating conditions with actions
        has_dest->pass = is_stuck;
        has_dest->fail = set_path_home;

        is_stuck->pass = redraw_path;
        is_stuck->fail = no_op;

        // add the returning tree root to the state table
        m_state_tbl[AiState::Type::returning]->setRoot(has_dest);
    }

    // set initial state
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
