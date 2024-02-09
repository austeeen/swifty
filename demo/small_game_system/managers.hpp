#include "common_includes.hpp"
#include "entities.hpp"
#include "game_context.hpp"
#include "object_container.hpp"

class System;

// Manager Base class
class Manager {
private:
    SharedGameContext * gameContext;

public:
    Manager(SharedGameContext * gameContext) : gameContext(gameContext) {}
};


class SystemManager: 
    public Manager, 
    virtual public Contains<System> {
private:
    
public:
    SystemManager(SharedGameContext * gameContext) : Manager(gameContext) {}
   
};

// EntityManager class
class EntityManager: 
    public Manager,
    virtual public Contains<Entity> {
private:
    int nextEntityID = 1;

    const int getNextEntityID() {
        nextEntityID += 1;
        return nextEntityID;
    }

public:
    EntityManager(SharedGameContext * gameContext) : Manager(gameContext) {}

    // Destroy an entity by ID
    void remove(const int entityID) {
        
    }

};

class UserInputManager: public Manager {
private:

public:
    UserInputManager(SharedGameContext * gameContext) : Manager(gameContext) {}
};