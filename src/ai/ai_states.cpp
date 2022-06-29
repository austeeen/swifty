#include "ai_states.hpp"
#include "../objects/ai_object.hpp"

AiState::AiState(AiObject* obj):
    m_obj(obj)
{}
void AiState::setRoot(Node* root)
{
    decision_root = root;
}
void AiState::processDecision() const
{
    Node* n = decision_root;
    while (n != nullptr) {
        n = n->exec(m_obj);
    }
}

/**************************************************************************************************/

Wandering::Wandering(AiObject* obj):
    AiState(obj)
{}
const AiState::Type Wandering::observe() const
{
    if (m_obj->targetDetected()) {
        return Type::stalking;
    }
    return Type::wandering;
}

/**************************************************************************************************/

Stalking::Stalking(AiObject* obj):
    AiState(obj)
{}
const AiState::Type Stalking::observe() const
{
    if (!m_obj->targetDetected()) {
        return Type::returning;
    }
    return Type::stalking;
}

/**************************************************************************************************/

Returning::Returning(AiObject* obj):
    AiState(obj)
{}
const AiState::Type Returning::observe() const
{
    if (m_obj->closeToHome()) {
        return Type::wandering;
    } else if (m_obj->targetDetected()) {
        return Type::stalking;
    }
    return Type::returning;
}
