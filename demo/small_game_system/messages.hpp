#include "common_includes.hpp"

// Message class representing a message that can be published
class Message {
public:
    virtual ~Message() = default;
};

struct CutsceneStartMessage : public Message {
    // Add any necessary data
};

struct CutsceneEndMessage : public Message {
    // Add any necessary data
};

// Example message type (you can create more message types as needed)
class EntityDestroyedMessage : public Message {
public:
    int entityId;

    EntityDestroyedMessage(int id) : entityId(id) {}
};