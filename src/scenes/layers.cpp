#include "layers.hpp"
#include "scene.hpp"

SceneLayer::SceneLayer(const int id, const std::string& name, Scene* scn):
    id(id),
    name(name),
    scene(scn)
{}

SceneLayer::~SceneLayer()
{
    scene = nullptr;
}

/**************************************************************************************************/

ImageLayer::ImageLayer(Scene* scn, tb::TileLayer& lyr):
    SceneLayer(lyr.id, lyr.name, scn),
    layer(lyr),
    render_texture(new sf::RenderTexture())
{
    tb::Tmx* tmx = scene->getTmx();
    render_texture->create(tmx->tilewidth * lyr.width, tmx->tileheight * lyr.height);
    vertex_array.resize(lyr.width * lyr.height * 4);
}

ImageLayer::~ImageLayer()
{
    delete render_texture;
    render_texture = nullptr;
}

void ImageLayer::build()
{
    render_texture->clear(sf::Color::Transparent);

    tb::Tmx* tmx = scene->getTmx();
    for (const tb::TextureRect& tile : layer.tiles)
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
        tb::Tileset cur_tileset = tmx->tilesets[indx];

        tb::Tile t;
        if (!tb::getTile(t, cur_tileset, (tile.gid - cur_tileset.firstgid))) {
            continue;
        }
        tb::Rect tr = t.texture;
        quads[0].texCoords = sf::Vector2f(tr.x,            tr.y);
        quads[1].texCoords = sf::Vector2f(tr.x + tr.width, tr.y);
        quads[2].texCoords = sf::Vector2f(tr.x + tr.width, tr.y  + tr.height);
        quads[3].texCoords = sf::Vector2f(tr.x,            tr.y  + tr.height);

        // render the texture to the surface
        render_texture->draw(quads, 4, sf::Quads, *scene->getRenderStates(cur_tileset.name));
    }
    render_texture->display();
}

void ImageLayer::render(sf::RenderWindow &window)
{
    window.draw(sf::Sprite(render_texture->getTexture()));
}

/**************************************************************************************************/

ObjectLayer::ObjectLayer(Scene* scn, tb::ObjectLayer& lyr):
    SceneLayer(lyr.id, lyr.name, scn),
    layer(lyr)
{}

ObjectLayer::~ObjectLayer() {
    for (auto& enty : entities) {
        delete enty;
    }
    entities.clear();
}

void ObjectLayer::build() {
    for (auto& enty : entities) {
        enty->build();
    }
}

void ObjectLayer::setUp() {
    for (auto& enty : entities) {
        enty->setUp();
    }
}

void ObjectLayer::update(const float dt) {
    for (auto& enty : entities) {
        enty->update(dt);
    }
}

void ObjectLayer::lateUpdate() {
    for (auto& enty : entities) {
        enty->lateUpdate();
    }
}

void ObjectLayer::render(sf::RenderWindow &window) {
    for (auto& enty : entities) {
        enty->render(window);
    }
}

void ObjectLayer::toggleDisplay()
{
    for (auto& enty : entities) {
        enty->toggleDisplay();
    }
}

/**************************************************************************************************/

BoundaryLayer::BoundaryLayer(Scene* scn, tb::ObjectLayer& lyr):
    ObjectLayer(scn, lyr),
    render_texture(new sf::RenderTexture())
{
    tb::Tmx* tmx = scene->getTmx();
    render_texture->create(tmx->tilewidth * tmx->width, tmx->tileheight * tmx->height);
    vertex_array.resize(tmx->width * tmx->height * 4);

    // TODO: set up tiles in object layer as a grid of linked tiles
}

void BoundaryLayer::build()
{
    // TODO: get tileset entry for texture/collision stuff

    render_texture->clear(sf::Color::Transparent);

    tb::Tmx* tmx = scene->getTmx();
    for (auto [id, tile] : layer.tilemap)
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
        tb::Tileset cur_tileset = tmx->tilesets[indx];

        tb::Tile t;
        if (!tb::getTile(t, cur_tileset, (tile.gid - cur_tileset.firstgid))) {
            continue;
        }

        for (const tb::Rect r : t.rects) {
            entities.push_back(new Boundary(sf::IntRect(tile.x + r.x, tile.y + r.y, r.width, r.height)));
        }

        tb::Rect tr = t.texture;
        quads[0].texCoords = sf::Vector2f(tr.x,            tr.y);
        quads[1].texCoords = sf::Vector2f(tr.x + tr.width, tr.y);
        quads[2].texCoords = sf::Vector2f(tr.x + tr.width, tr.y  + tr.height);
        quads[3].texCoords = sf::Vector2f(tr.x,            tr.y  + tr.height);

        // render the texture to the surface
        render_texture->draw(quads, 4, sf::Quads, *scene->getRenderStates(cur_tileset.name));
    }
    render_texture->display();
}

void BoundaryLayer::setUp()
{}

void BoundaryLayer::update(const float dt)
{}

void BoundaryLayer::lateUpdate()
{}

void BoundaryLayer::render(sf::RenderWindow &window)
{
    // todo -- may look at rendering all 'static entities' to a constant surface and list the rects
    // separately
    window.draw(sf::Sprite(render_texture->getTexture()));
}

/**************************************************************************************************/

PlatformLayer::PlatformLayer(Scene* scn, tb::ObjectLayer& lyr):
    ObjectLayer(scn, lyr)
{

}

void PlatformLayer::build()
{
    // TODO: this should look similar to ObjectLayer<Boundary>::build()
}

void PlatformLayer::setUp()
{}

/**************************************************************************************************/

GameObjectLayer::GameObjectLayer(Scene* scn, tb::ObjectLayer& lyr):
    ObjectLayer(scn, lyr)
{

}

void GameObjectLayer::build()
{
    // TODO -- create spider/cat/etc, then build them
}
