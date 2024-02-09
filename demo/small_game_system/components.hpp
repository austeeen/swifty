#include "common_includes.hpp"
#include "object_properties.hpp"

// Component base class
class Component {
protected:
    Entity * parent;

public:
    Component(Entity * parent) : parent(parent) {}
    virtual ~Component() {
        parent = nullptr;
    };
};

// Sprite component
class SpriteComponent : 
    public Updated<Component>, 
    public Rendered<Component> {
public:
    std::string spritePath;  // Path to the sprite image file
    int width, height;       // Dimensions of the sprite

    SpriteComponent(Entity * parent, const std::string& path, int w, int h)
        : Component(parent),
          Updated<Component>(parent), 
          Rendered<Component>(parent),
          spritePath(path), 
          width(w), 
          height(h) {}

    void update() override {
        // Update sprite-specific logic here
        std::cout << "Updating SpriteComponent for " << parent->getID() << std::endl;
    }

    void render() override {
        std::cout << "Rendering SpriteComponent for " << parent->getID() << std::endl;
    }
};

class UserInputComponent : public Component {
private:
    UserInputManager * inputManager;

public:
    UserInputComponent(Entity * parent, UserInputManager * inputManager)
        : Component(parent),
          inputManager(inputManager)
    {}
};

class CombatComponent : public Component {
public:
    int health;
};

class WeaponComponent : public Component {
public:
    int damage;
    // Add other weapon-related attributes
};

class CutsceneComponent : public Component {
public:
    bool active;        // Is the cutscene currently active?
    int currentFrame;   // Current frame of the cutscene
    int totalFrames;    // Total frames in the cutscene
    // Add other necessary data
};

