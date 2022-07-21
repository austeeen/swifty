#ifndef SCN_LAYERS_HPP
#define SCN_LAYERS_HPP

#include "../common.hpp"
#include "../objects/all.hpp"

class Scene;

class SceneLayer
{
public:
    SceneLayer(const int id, const std::string& name, Scene* scn);
    virtual ~SceneLayer();

protected:
    const int id;
    const std::string name;
    Scene* scene;
};

/**************************************************************************************************/

class ImageLayer : public SceneLayer
{
public:
    ImageLayer(Scene* scn, tb::TileLayer& lyr);
    ~ImageLayer();
    virtual void build();
    virtual void render(sf::RenderWindow &window);

private:
    tb::TileLayer layer;
    sf::VertexArray vertex_array;
    sf::RenderTexture* render_texture;
};

/**************************************************************************************************/

class ObjectLayer : public SceneLayer
{
public:
    ObjectLayer(Scene* scn, tb::ObjectLayer& lyr);
    ~ObjectLayer();
    virtual void build();
    virtual void setUp();
    virtual void update(const float dt);
    virtual void lateUpdate();
    virtual void render(sf::RenderWindow &window);

    virtual void toggleDisplay();

protected:
    tb::ObjectLayer layer;
    std::vector<ObjectBase*> entities;
};

/**************************************************************************************************/

class BoundaryLayer : public ObjectLayer
{
public:
    BoundaryLayer(Scene* scn, tb::ObjectLayer& lyr);
    void build() override;
    void setUp() override;
    void update(const float dt) override;
    void lateUpdate() override;
    void render(sf::RenderWindow &window) override;
};

/**************************************************************************************************/

class PlatformLayer : public ObjectLayer
{
public:
    PlatformLayer(Scene* scn, tb::ObjectLayer& lyr);
    void build() override;
    void setUp() override;
};

/**************************************************************************************************/

class GameObjectLayer: public ObjectLayer
{
public:
    GameObjectLayer(Scene* scn, tb::ObjectLayer& lyr);
    void build() override;
};


#endif // SCN_LAYERS_HPP
