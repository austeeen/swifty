#ifndef AI_STATES_HPP
#define AI_STATES_HPP

#include "ai_core.hpp"

class AiState
{
public:
    enum class Type { wandering, stalking, returning };

    AiState(AiObject* obj);
    void setRoot(Node* root);
    virtual const Type observe() const =0;
    void processDecision() const;

protected:
    AiObject* m_obj;
    Node* decision_root;
};

class Wandering: public AiState
{
public:
    Wandering(AiObject* obj);
    const Type observe() const override;
};

class Stalking: public AiState
{
public:
    Stalking(AiObject* obj);
    const Type observe() const override;
};

class Returning: public AiState
{
public:
    Returning(AiObject* obj);
    const Type observe() const override;
};

#endif // AI_STATES_HPP
