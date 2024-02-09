#include "common_includes.hpp"
#include "components.hpp"
#include "managers.hpp"
#include "game_context.hpp"
#include "object_properties.hpp"

// System Base class
class System {
protected:
    SharedGameContext * gameContext;
    SystemManager * parent;

public:
    System(SharedGameContext * gameContext, SystemManager * parent) 
        : gameContext(gameContext),
          parent(parent)
    {}
};


// class CombatSystem: public System {
// public:
//     CombatSystem(SharedGameContext * gameContext) : System(gameContext) {}

//     static void performAttack(Entity& attacker, Entity& target) {
//         CombatComponent* attackerCombat = attacker.getComponent<CombatComponent>();
//         WeaponComponent* attackerWeapon = attacker.getComponent<WeaponComponent>();

//         CombatComponent* targetCombat = target.getComponent<CombatComponent>();

//         // Perform damage calculation
//         int damageDealt = attackerWeapon->damage;
//         targetCombat->health -= damageDealt;

//         // Check if the target has been defeated
//         if (targetCombat->health <= 0) {
//             // Handle defeat logic (e.g., remove entity, trigger events, etc.)
//         }
//     }
// };

// class InputHandlerSystem: public System {
// private:
//     Entity * inputTarget;
//     InputBinding * inputBinding;

// public:
//     InputHandlerSystem(SharedGameContext * gameContext) : System(gameContext) {}

//     void handleInput() {
//         // Example: Pressing a key triggers an attack
//         if (inputBinding->moveKeyLeft()) {
//             inputTarget->moveLeft();
//         } else if (inputBinding->moveKeyRight()) {
//             inputTarget->moveRight();
//         }
//     }
// };
