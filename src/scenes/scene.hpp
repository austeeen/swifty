#ifndef SCN_SCENE_HPP
#define SCN_SCENE_HPP

#include "../common.hpp"
#include "../io/devices.hpp"
#include "../sys_collision.hpp"

class ImageLayer;
template <class T> class SceneLayer;

struct ImageResource
{
    ImageResource(const tb::Image& rsrc);
    sf::Texture img_texture;
    sf::RenderStates* render_states;
};

class Scene
{
public:
    Scene(const std::string& tmx_fp);
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
    sf::RenderStates* getRenderStates(const std::string& img_src) const {
        return img_srcs.at(img_src)->render_states;
    };

protected:
    tb::Tmx* tmx;
    std::map<const std::string, ImageResource*> img_srcs;
    std::vector<ImageLayer*> img_layers;
    std::vector<SceneLayer<tb::ObjectLayer>*> obj_layers;
    CollisionSystem collision_system;
};

#endif // TLD_TILEMAP_HPP
