#include "common_includes.hpp"
#include "notifications.hpp"

// Entity class
class Entity : public Subscriber {
private:
    const int id;
    std::unordered_map<std::type_index, std::shared_ptr<Component>> allComponents;
    std::unordered_map<std::type_index, std::vector<Component&>> componentTable;

public:
    Entity(const int entityId) : id(entityId) {
        std::cout << "Entity " << entityId << " created." << std::endl;
    }

    int getID() const { return id; }

    // Add a component to the entity
    template <typename T, typename... Args>
    void addComponent(Args&&... args) {
        std::shared_ptr<T> component = std::make_shared<T>(this, std::forward<Args>(args)...);
        components[typeid(T)] = component;
    }

    // Remove a component from the entity's component vector
    template <typename T>
    void removeComponent(std::vector<T> * cmpVector, T * cmp) {
        auto it = cmpVector.find(cmp);
        if (it != components.end()) {
            cmpVector.erase(it);
        }
    }

    // Remove a component from the entity
    template <typename T>
    void removeComponent() {
        auto it = components.find(typeid(T));
        if (it != components.end()) {
            delete it->second;
            it->second = nullptr;
            components.erase(it);
        }
    }

    // Get a component from the entity
    template <typename T>
    T* getComponent() const {
        auto it = components.find(typeid(T));
        if (it != components.end()) {
            return dynamic_cast<T*>(it->second);
        }
        return nullptr;
    }

    template <typename T>
    void registerComponent(T & cmp) {
        componentTable[typeid(T)].push_back(cmp);
    }

    template <typename T>
    void unRegisterComponent(T & cmp) {
        auto it = componentTable.find(typeid(T));
        if (it != componentTable.end()) {
            components.erase(it);
        }
    }

    /* LoadTimeComponent functions */
    virtual void build() {
        for (LoadTimeComponent& cmp : componentTable.at(typeid(LoadTimeComponent))) {
            cmp.build();
        }
    }

    virtual void setUp() {
        for (LoadTimeComponent& cmp : componentTable.at(typeid(LoadTimeComponent))) {
           cmp.setUp();
        }
    }

    /* UpdatedComponent functions */
    void update() {
        for (UpdatedComponent& cmp : componentTable.at(typeid(UpdatedComponent))) {
            cmp.update();
        }
    }

    void lateUpdate() {
        for (UpdatedComponent& cmp : componentTable.at(typeid(UpdatedComponent))) {
            cmp.lateUpdate();
        }
    }

    /* RenderedComponent functions */
    virtual void render() {
        for (RenderedComponent& cmp : componentTable.at(typeid(RenderedComponent))) {
            cmp.render();
        }
    }

    /* Subscriber */
    void onNotify(const Message& message) override {
        if (const auto* entityDestroyedMessage = dynamic_cast<const EntityDestroyedMessage*>(&message)) {
            std::cout << "Entity with ID " << entityDestroyedMessage->entityId << " has been destroyed." << std::endl;
        }
    }
};