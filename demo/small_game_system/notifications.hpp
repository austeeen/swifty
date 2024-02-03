#include "common_includes.hpp"
#include "messages.hpp"

// Subscriber interface
class Subscriber {
public:
    virtual ~Subscriber() = default;
    virtual void onNotify(const Message& message) = 0;
};

// Publisher class to manage subscribers and dispatch messages
class Publisher {
private:
    std::unordered_map<std::type_index, std::vector<Subscriber*>> subscribers;

public:
    // Subscribe a subscriber to a specific message type
    template <typename T>
    void subscribe(Subscriber* subscriber) {
        subscribers[typeid(T)].emplace_back(subscriber);
    }

    // Unsubscribe a subscriber from a specific message type
    template <typename T>
    void unsubscribe(Subscriber* subscriber) {
        auto& subscribersOfType = subscribers[typeid(T)];
        subscribersOfType.erase(
            std::remove(subscribersOfType.begin(), subscribersOfType.end(), subscriber),
            subscribersOfType.end());
    }

    // Publish a message to all subscribers of its type
    template <typename T>
    void publish(const T& message) {
        for (Subscriber* subscriber : subscribers[typeid(T)]) {
            subscriber->onNotify(message);
        }
    }
};
