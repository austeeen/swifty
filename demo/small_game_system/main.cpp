/*
* Purely for conceptual purposes. This is not intended to build or work.
*/

#include "game_context.hpp"
#include "managers.hpp"
#include "systems.hpp"
#include "entities.hpp"
#include "notifications.hpp"


int main() {

    SharedGameContext gameContext;
    gameContext.addManager<EntityManager>();
    gameContext.addManager<UserInputManager>();
    gameContext.addSystem<EntityLoaderSystem>();
    gameContext.addSystem<EntityUpdateSystem>();
    gameContext.addSystem<EntityRenderSystem>();
    
    // Create entities
    Entity * playerEntity = gameContext.getManager<EntityManager>()->createEntity<Entity>();
    Entity * enemyEntity = gameContext.getManager<EntityManager>()->createEntity<Entity>();
    
    // Add components to entities
    playerEntity->addComponent<SpriteComponent>("path/to/player_sprite.png", 32, 32);
    playerEntity->addComponent<CombatComponent>();
    playerEntity->addComponent<WeaponComponent>();
    playerEntity->addComponent<UserInputComponent>(gameContext.getManager<UserInputManager>());

    enemyEntity->addComponent<SpriteComponent>("path/to/enemy_sprite.png", 32, 32);
    enemyEntity->addComponent<CombatComponent>();
    enemyEntity->addComponent<WeaponComponent>();

    std::vector<Entity*> allEntities = gameContext.getManager<EntityManager>()->getAllEntities();
    gameContext.getSystem<EntityLoaderSystem>()->loadEntities(allEntities);

    // Game loop:
    gameContext.getSystem<InputHandlerSystem>()->handleInput(playerEntity);
    gameContext.getSystem<EntityUpdateSystem>()->updateEntities(allEntities);
    gameContext.getSystem<EntityUpdateSystem>()->lateUpdateEntities(allEntities);
    gameContext.getSystem<EntityRenderSystem>()->renderEntities(allEntities);

    // Subscribe the Player to EntityDestroyedMessage
    gameContext.getPublisher()->subscribe<EntityDestroyedMessage>(playerEntity);

    // Simulate an entity being destroyed
    gameContext.getManager<EntityManager>()->destroyEntity(enemyEntity);
    EntityDestroyedMessage entityDestroyedMessage(enemyEntity->getID());
    gameContext.getPublisher()->publish(entityDestroyedMessage);

    // Clean up
    gameContext.getPublisher()->unsubscribe<EntityDestroyedMessage>(playerEntity);
    gameContext.getManager<EntityManager>()->destroyEntity(playerEntity);

    return 0;
}