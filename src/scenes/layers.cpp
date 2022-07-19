#include "layers.hpp"

template <> void ObjectLayer<Boundary>::build()
{
    // TODO: set up tiles in object layer as a grid of linked tiles

    // TODO: get tileset entry for texture/collision stuff
    for (auto& obj : objects) {
        // TODO: implement tracer agent for combining basic rects
        obj->build();
    }
}

template <> void ObjectLayer<Boundary>::setUp()
{}

template <> void ObjectLayer<Boundary>::update(const float dt)
{}

template <> void ObjectLayer<Boundary>::lateUpdate()
{}

template <> void ObjectLayer<Boundary>::render(sf::RenderWindow &window)
{
    // todo -- may look at rendering all 'static objects' to a constant surface and list the rects
    // separately
    for (auto& obj : objects) {
        obj->render(window);
    }
}

/**************************************************************************************************/

template <> void ObjectLayer<MovingPlatform>::build()
{
    // TODO: this should look similar to ObjectLayer<Boundary>::build()
}

template <> void ObjectLayer<MovingPlatform>::setUp()
{}

/**************************************************************************************************/

template <> void ObjectLayer<GameObject>::build()
{
    // TODO -- create spider/cat/etc, then build them
}

/**************************************************************************************************/
