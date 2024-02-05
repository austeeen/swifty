#include "common_includes.hpp"
#include "entities.hpp"
#include "game_context.hpp"

// Manager Base class
class Manager {
private:
    SharedGameContext * gameContext;

public:
    Manager(SharedGameContext * gameContext) : gameContext(gameContext) {}
};

// EntityManager class
class EntityManager: public Manager {
private:
    int nextEntityID = 1;
    std::vector<Entity*> entities;

    const int getNextEntityID() {
        nextEntityID += 1;
        return nextEntityID;
    }

public:
    EntityManager(SharedGameContext * gameContext) : Manager(gameContext) {}

    // Create a new entity
    template <typename T, typename... Args>
    T * createEntity(Args&&... args) {
        T * newEntity = std::make_shared<T>(getNextEntityID(), std::forward<Args>(args)...);
        entities.emplace_back(newEntity);
        return newEntity;
    }

    // Destroy an entity
    void destroyEntity(Entity * entity) {
        for (auto iter = entities.begin(); iter < entities.end(); iter++) {
            if ((*iter) == entity) {
                delete *iter;
                entities.erase(iter);
                break;
            }
        }
    }

    // Destroy an entity by ID
    void destroyEntity(const int entityID) {
        for (auto iter = entities.begin(); iter < entities.end(); iter++) {
            if ((*iter)->getID() == entityID) {
                delete *iter;
                entities.erase(iter);
            }
        }
    }

    std::vector<Entity*>& getAllEntities() {
        return entities;
    }

    // Get all entities of a specific type
    template <typename T>
    std::vector<T*> getEntities() {
        std::vector<T*> matches;
        for (auto ent : entities) {
            if (dynamic_cast<T*>(ent) != nullptr) {
                matches.push_back(ent);
            }
        }
        return matches;
    }

    // Get all entities with a specific component
    template <typename T>
    std::vector<Entity> getEntitiesWithComponent() const {
        std::vector<Entity> result;
        for (const Entity& entity : entities) {
            if (entity.getComponent<T>() != nullptr) {
                result.push_back(entity);
            }
        }
        return result;
    }
};

class UserInputManager: public Manager {
private:

public:
    UserInputManager(SharedGameContext * gameContext) : Manager(gameContext) {}
};