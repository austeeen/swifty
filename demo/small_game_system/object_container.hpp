#include "common_includes.hpp"

template <class T>
class Contains {
protected:
    std::unordered_map<std::type_index, T*> allObjects;
    std::unordered_map<std::type_index, std::vector<T*>> objectTable;

public:

    template <typename K, typename... Args>
    K * add(Args && ... args) {
        K * obj = new K(this, std::forward<Args>(args)...);
        allObjects[typeid(K)] = obj;
        return obj;
    }

    template <typename K>
    void remove(std::vector<K> * objVector, K * obj) {
        auto it = objVector.find(obj);
        if (it != allObjects.end()) {
            objVector.erase(it);
        }
    }

    template <typename K>
    void remove() {
        auto it = allObjects.find(typeid(K));
        if (it != allObjects.end()) {
            delete it->second;
            it->second = nullptr;
            allObjects.erase(it);
        }
    }

    template <typename K>
    K* get() const {
        auto it = allObjects.find(typeid(K));
        if (it != allObjects.end()) {
            return dynamic_cast<K*>(it->second);
        }
        return nullptr;
    }

        // Get all entities of a specific type
    template <typename K>
    std::vector<K*>& getAll() {
        return objectTable[typeid(K)];
    }

    template <typename K>
    void doRegister(K * obj) {
        objectTable[typeid(K)].push_back(obj);
    }

    template <typename K>
    void unRegister(K * obj) {
        auto it = objectTable.find(typeid(K));
        if (it != objectTable.end()) {
            this->remove<K>(*it, obj);
        }
    }
};