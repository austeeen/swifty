#ifndef SCN_LAYERS_HPP
#define SCN_LAYERS_HPP

#include "../common.hpp"
#include "../objects/all.hpp"
#include "scene.hpp"


class SceneLayer
{
public:
    SceneLayer(const int id, const std::string& name, Scene* scn);
    ~SceneLayer();

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

template <class T>
class ObjectLayer : public SceneLayer
{
public:
    ObjectLayer(Scene* scn, tb::ObjectLayer& lyr);
    ~ObjectLayer();
    void build();
    void setUp();
    void update(const float dt);
    void lateUpdate();
    void render(sf::RenderWindow &window);

protected:
    tb::ObjectLayer layer;
    std::vector<T*> objects;

};

// template <> class ObjectLayer<Boundary>;
// template <> class ObjectLayer<MovingPlatform>;
// template <> class ObjectLayer<GameObject>;

/**************************************************************************************************/


#endif // SCN_LAYERS_HPP
