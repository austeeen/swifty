#ifndef SCN_SCENE_HPP
#define SCN_SCENE_HPP

#include "../common.hpp"
#include "layers.hpp"


class Scene
{
public:
    Scene(const char* tmx_fp);
    ~Scene();
    void build();
    void setUp();

    void update(const float dt);
    void lateupdate();
    void render(sf::RenderWindow &window);

    tb::Tmx* getTmx() const { return tmx; };

protected:
    tb::Tmx* tmx;
    std::vector<Layer*> layers;
};

#endif // TLD_TILEMAP_HPP
