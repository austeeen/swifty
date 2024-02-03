#include "common_includes.hpp"

// Component base class
class Component {
protected:
    Entity * parent;

public:
    Component(Entity * parent) : parent(parent) {}
    virtual ~Component() {
        parent = nullptr;
    };
    virtual void update() = 0;
};


class LoadTimeComponent: virtual public Component {
public:
    LoadTimeComponent(Entity * parent)
        : Component(parent) {
        parent->registerComponent<LoadTimeComponent>(*this);
    }

    virtual ~LoadTimeComponent() {
        parent->unRegisterComponent<LoadTimeComponent>(*this);
    }

    virtual void build() = 0;
    virtual void setUp() = 0;
};

class UpdatedComponent: virtual public Component {
public:
    UpdatedComponent(Entity * parent)
        : Component(parent) {
        parent->registerComponent<UpdatedComponent>(*this);
    }

    virtual ~UpdatedComponent() {
        parent->unRegisterComponent<UpdatedComponent>(*this);
    }

    virtual void update() = 0;
    virtual void lateUpdate() = 0;
};

class RenderedComponent: virtual public Component {
public:
    RenderedComponent(Entity * parent)
        : Component(parent) {
        parent->registerComponent<RenderedComponent>(*this);
    }
    virtual ~RenderedComponent() {
        parent->unRegisterComponent<RenderedComponent>(*this);
    }

    virtual void render() = 0;
};


// Sprite component
class SpriteComponent : 
    public UpdatedComponent, 
    public RenderedComponent {
public:
    std::string spritePath;  // Path to the sprite image file
    int width, height;       // Dimensions of the sprite

    SpriteComponent(Entity * parent, const std::string& path, int w, int h)
        : Component(parent),
          UpdatedComponent(parent), 
          RenderedComponent(parent),
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
