#include "common_includes.hpp"
#include "notifications.hpp"
#include "object_properties.hpp"

// Entity class
class Entity : 
    public Subscriber, 
    virtual public Contains<Component> {
private:
    const int id;
    EntityManager * parent;

public:
    Entity(EntityManager * parent, const int entityId): 
        parent(parent),
        id(entityId) {
        std::cout << "Entity " << entityId << " created." << std::endl;
    }

    int getID() const { return id; }

    /* Subscriber */
    void onNotify(const Message& message) override {
        if (const auto* entityDestroyedMessage = dynamic_cast<const EntityDestroyedMessage*>(&message)) {
            std::cout << "Entity with ID " << entityDestroyedMessage->entityId << " has been destroyed." << std::endl;
        }
    }
};

class PlayerEntity: 
    public Entity,
    virtual public LoadTime<Entity>,
    virtual public Updated<Entity>,
    virtual public Rendered<Entity> {
private:

public:
    PlayerEntity(EntityManager * parent, const int entityId): 
        Entity(parent, entityId),
        LoadTime<Entity>(parent)
    {}
};
