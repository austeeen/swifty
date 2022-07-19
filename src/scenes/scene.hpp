#ifndef SCN_SCENE_HPP
#define SCN_SCENE_HPP

#include "../common.hpp"
#include "layers.hpp"

class ImageResource
{
    sf::Texture img_texture;
    sf::RenderStates* render_states;
};

class Scene
{
public:
    Scene(const char* tmx_fp);
    ~Scene();
    void build();
    void setUp();
    void onUserInput(InputDevice *io_device);
    void onUserEvent(sf::Event &event);
    void update(const float dt);
    void lateUpdate();
    void render(sf::RenderWindow &window);

    const sf::Vector2f& getViewportCenter() const;

    tb::Tmx* getTmx() const { return tmx; };

protected:
    tb::Tmx* tmx;
    std::map<const std::string, ImageResource*> img_srcs;
    std::vector<Layer*> layers;

    std::shared_ptr<Player> player;
    std::vector<std::shared_ptr<AiObject>> enemies;
    std::vector<std::shared_ptr<MovingPlatform>> platforms;
    std::vector<std::shared_ptr<Boundary>> boundaries;
    CollisionSystem collision_system;
};

#endif // TLD_TILEMAP_HPP
