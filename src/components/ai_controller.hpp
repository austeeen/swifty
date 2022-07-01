#ifndef CMP_AICONTROLLER_HPP
#define CMP_AICONTROLLER_HPP

#include "component_base.hpp"
#include "../ai/ai_states.hpp"

// future state: will be a base class for various implementations of ai behaviors

class AiController: public Component
{
public:
    AiController(AiObject* obj);
    ~AiController();
    void build() override;
    void setUp() override;
    void update(const float dt) override;
    const bool stuckTimedout() const;

private:
    AiObject* m_obj;
    std::map<const AiState::Type, AiState*> m_state_tbl;
    AiState::Type m_state;
    float stuck_dt;
    const float stuck_timeout = STUCK_TIMEOUT;
    // todo -- write out moving/jumping/etc stuff and switch body/animation states
};

#endif // CMP_AICONTROLLER_HPP
