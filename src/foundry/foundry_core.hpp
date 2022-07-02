#ifndef FND_CORE_HPP
#define FND_CORE_HPP

#include "../common.hpp"

enum class LayerType {
    BACKGROUND, WALL, OBJECT, BOUNDARY, PLATFORM, DYNAMIC, TERRAIN, LOCATION, ZONE
};
const std::map<const std::string, const LayerType> asLayerType {
    {"background", LayerType::BACKGROUND},
    {"wall", LayerType::WALL},
    {"object", LayerType::OBJECT},
    {"boundary", LayerType::BOUNDARY},
    {"platform", LayerType::PLATFORM},
    {"dynamic", LayerType::DYNAMIC},
    {"terrain", LayerType::TERRAIN},
    {"location", LayerType::LOCATION},
    {"zone", LayerType::ZONE}
};

#endif // FND_CORE_HPP
