#include "common_includes.hpp"
#include "notifications.hpp"

class System;
class Manager;

class SharedGameContext {
private:
    Publisher * publisher;
    std::unordered_map<std::type_index, std::shared_ptr<System>>  allSystems;
    std::unordered_map<std::type_index, std::shared_ptr<Manager>> allManagers;

public:
    SharedGameContext() {
        publisher = new Publisher();
    }

    Publisher * getPublisher() {
        return publisher;
    }

    /* SYSTEMS */
    template <typename T, typename... Args>
    T*  addSystem(Args&&... args) {
        std::shared_ptr<T> system = std::make_shared<T>(this, std::forward<Args>(args)...);
        allSystems[typeid(T)] = system;
        return system;
    }

    template <typename T>
    void removeSystem() {
        auto it = allSystems.find(typeid(T));
        if (it != allSystems.end()) {
            delete it->second;
            it->second = nullptr;
            allSystems.erase(it);
        }
    }

    template <typename T>
    T* getSystem() const {
        auto it = allSystems.find(typeid(T));
        if (it != allSystems.end()) {
            return dynamic_cast<T*>(it->second);
        }
        return nullptr;
    }

    /* MANAGERS */
    template <typename T, typename... Args>
    void addManager(Args&&... args) {
        std::shared_ptr<T> manager = std::make_shared<T>(this, std::forward<Args>(args)...);
        allManagers[typeid(T)] = manager;
    }

    template <typename T>
    void removeManager() {
        auto it = allManagers.find(typeid(T));
        if (it != allManagers.end()) {
            delete it->second;
            it->second = nullptr;
            allManagers.erase(it);
        }
    }

    template <typename T>
    T* getManager() const {
        auto it = allManagers.find(typeid(T));
        if (it != allManagers.end()) {
            return dynamic_cast<T*>(it->second);
        }
        return nullptr;
    }

};