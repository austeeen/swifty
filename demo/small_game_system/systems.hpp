#include "common_includes.hpp"
#include "components.hpp"
#include "managers.hpp"
#include "game_context.hpp"

// System Base class
class System {
private:
    SharedGameContext * gameContext;

public:
    System(SharedGameContext * gameContext) : gameContext(gameContext) {}
};

class EntityLoaderSystem: public System {
public:
    EntityLoaderSystem(SharedGameContext * gameContext) : System(gameContext) {}

    void buildEntities(std::vector<Entity*>& entities) {
        for (Entity * entity : entities) {
            entity->build();
        }
    }

    void setUpEntities(std::vector<Entity*>& entities) {
        for (Entity * entity : entities) {
            entity->setUp();
        } 
    }

    void loadEntities(std::vector<Entity*>& entities) {
        buildEntities(entities);
        setUpEntities(entities);
    }
};

class EntityUpdateSystem: public System {
public:
    EntityUpdateSystem(SharedGameContext * gameContext) : System(gameContext) {}

    void updateEntities(std::vector<Entity*>& entities) {
        for (Entity * entity : entities) {
            entity->update();
        }
    }

    void lateUpdateEntities(std::vector<Entity*>& entities) {
        for (Entity * entity : entities) {
            entity->lateUpdate();
        } 
    }
};

class EntityRenderSystem: public System {
public:
    EntityRenderSystem(SharedGameContext * gameContext) : System(gameContext) {}

    void renderEntities(std::vector<Entity*>& entities) {
        for (Entity * entity : entities) {
            entity->render();
        }
    }
};

class CombatSystem: public System {
public:
    CombatSystem(SharedGameContext * gameContext) : System(gameContext) {}

    static void performAttack(Entity& attacker, Entity& target) {
        CombatComponent* attackerCombat = attacker.getComponent<CombatComponent>();
        WeaponComponent* attackerWeapon = attacker.getComponent<WeaponComponent>();

        CombatComponent* targetCombat = target.getComponent<CombatComponent>();

        // Perform damage calculation
        int damageDealt = attackerWeapon->damage;
        targetCombat->health -= damageDealt;

        // Check if the target has been defeated
        if (targetCombat->health <= 0) {
            // Handle defeat logic (e.g., remove entity, trigger events, etc.)
        }
    }
};

class InputHandlerSystem: public System {
private:
    Entity * inputTarget;
    InputBinding * inputBinding;

public:
    InputHandlerSystem(SharedGameContext * gameContext) : System(gameContext) {}

    void 

    void handleInput() {
        // Example: Pressing a key triggers an attack
        if (inputBinding->moveKeyLeft()) {
            inputTarget->moveLeft();
        } else if (inputBinding->moveKeyRight()) {
            inputTarget->moveRight();
        }
    }
};
