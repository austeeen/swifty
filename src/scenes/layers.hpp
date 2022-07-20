#ifndef SCN_LAYERS_HPP
#define SCN_LAYERS_HPP

#include "../common.hpp"
#include "../objects/all.hpp"
#include "scene.hpp"

template <class LayerType> class SceneLayer
{
public:
    SceneLayer(Scene* scn, LayerType& lyr):
        id(lyr.id),
        name(lyr.name),
        scene(scn),
        lyr(lyr)
    {}

    ~SceneLayer()
    {
        scene = nullptr;
    };

protected:
    const int id;
    const std::string name;
    Scene* scene;
    LayerType lyr;

};

/**************************************************************************************************/

class ImageLayer : public SceneLayer<tb::TileLayer>
{
public:
    ImageLayer(Scene* scn, tb::TileLayer& lyr):
        SceneLayer<tb::TileLayer>(scn, lyr),
        render_texture(new sf::RenderTexture())
    {
        tb::Tmx* tmx = scene->getTmx();
        render_texture->create(tmx->tilewidth * lyr.width, tmx->tileheight * lyr.height);
        vertex_array.resize(lyr.width * lyr.height * 4);
    }

    ~ImageLayer()
    {
        delete render_texture;
        render_texture = nullptr;
    }

    virtual void build()
    {
        render_texture->clear(sf::Color::Transparent);

        tb::Tmx* tmx = scene->getTmx();
        tb::Tileset* cur_tileset;
        for (const tb::TextureRect& tile : lyr.tiles)
        {
            // Set tile's position
            sf::Vertex *quads = &vertex_array[tile.id * 4];
            quads[0].position = sf::Vector2f(tile.x,            tile.y);
            quads[1].position = sf::Vector2f(tile.x + tile.width, tile.y);
            quads[2].position = sf::Vector2f(tile.x + tile.width, tile.y  + tile.height);
            quads[3].position = sf::Vector2f(tile.x,            tile.y  + tile.height);

            // set tile's texture rect
            int indx = 0; // arbitrary number
            if (!tb::getTileset(indx, *tmx, tile.gid)) {
                continue;
            }
            *cur_tileset = tmx->tilesets[indx];

            tb::Tile* t;
            if (!tb::getTile(*t, *cur_tileset, (tile.gid - cur_tileset->firstgid))) {
                continue;
            }
            tb::Rect tr = t->texture;
            quads[0].texCoords = sf::Vector2f(tr.x,            tr.y);
            quads[1].texCoords = sf::Vector2f(tr.x + tr.width, tr.y);
            quads[2].texCoords = sf::Vector2f(tr.x + tr.width, tr.y  + tr.height);
            quads[3].texCoords = sf::Vector2f(tr.x,            tr.y  + tr.height);

            // render the texture to the surface
            render_texture->draw(quads, 4, sf::Quads, *scene->getRenderStates(cur_tileset->name));
        }
        render_texture->display();
    }

    virtual void render(sf::RenderWindow &window)
    {
        window.draw(sf::Sprite(render_texture->getTexture()));
    }

private:
    sf::VertexArray vertex_array;
    sf::RenderTexture* render_texture;
};

/**************************************************************************************************/

template <class ObjType> class ObjectLayer : public SceneLayer<tb::ObjectLayer>
{
public:
    ObjectLayer(Scene* scn, tb::ObjectLayer& lyr):
        SceneLayer<tb::ObjectLayer>(scn, lyr)
    {
        for (auto& r : lyr.rects) {
            objects.push_back(new ObjType(this, r));
        }
    }

    ~ObjectLayer() {
        for (auto& obj : objects) {
            delete obj;
        }
        objects.clear();
    }

    void build() {
        for (auto& obj : objects) {
            obj->build();
        }
    }

    void setUp() {
        for (auto& obj : objects) {
            obj->setUp();
        }
    }

    void update(const float dt) {
        for (auto& obj : objects) {
            obj->update(dt);
        }
    }

    void lateUpdate() {
        for (auto& obj : objects) {
            obj->lateUpdate();
        }
    }

    void render(sf::RenderWindow &window) {
        for (auto& obj : objects) {
            obj->render(window);
        }
    }

protected:
    std::vector<ObjType*> objects;

};

template <> class ObjectLayer<Boundary>;
template <> class ObjectLayer<MovingPlatform>;
template <> class ObjectLayer<GameObject>;

/**************************************************************************************************/


#endif // SCN_LAYERS_HPP
