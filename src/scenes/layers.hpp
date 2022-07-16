#ifndef SCN_LAYERS_HPP
#define SCN_LAYERS_HPP

#include "../common.hpp"
#include "objects/all.hpp"

class Scene;

class Layer
{
public:
    Layer(Scene* scn, tb::Layer& tb_lyr);
    ~Layer();

    virtual void build() = 0;
    virtual void setUp() = 0;

    virtual void update(const float dt) { };
    virtual void lateUpdate() { };
    virtual void render(sf::RenderWindow &window) { };

protected:
    const int id;
    const std::string name;
};

class ImageLayer: public Layer
{
public:
    Layer(Scene* scn, tb::TileLayer& tb_lyr);
    void build() override;
    void setUp() override;
    void render(sf::RenderWindow &window) override;

private:
    sf::VertexArray vertex_array;
    sf::RenderTexture* render_texture;
};

class StaticLayer: public Layer
{
public:
    Layer(Scene* scn, tb::ObjectLayer& tb_lyr);
    void build() override;
    void setUp() override;

private:
    std::vector<std::shared_ptr<Boundary>> boundaries;
};

class SceneObjects: public Layer
{
public:
    Layer(Scene* scn, tb::ObjectLayer& tb_lyr);
    void build() override;
    void setUp() override;
    void update(const float dt) override;
    void lateUpdate() override;
    void render(sf::RenderWindow &window) override;

private:
    std::vector<std::shared_ptr<MovingPlatform>> platforms;
};

class GameObjects: public Layer
{
public:
    Layer(Scene* scn, tb::ObjectLayer& tb_lyr);
    void build() override;
    void setUp() override;
    void update(const float dt) override;
    void lateUpdate() override;
    void render(sf::RenderWindow &window) override;

private:
    std::shared_ptr<Player> player;
    std::vector<std::shared_ptr<AiObject>> enemies;
};

#endif // SCN_LAYERS_HPP
