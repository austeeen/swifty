#include "typedefs.hpp"

namespace out {
    const std::string toStr(const ObjectState s)
    {
        switch(s) {
            case ObjectState::idle: { return "idle"; }
            case ObjectState::running: { return "running"; }
            case ObjectState::jumping: { return "jumping"; }
            case ObjectState::falling: { return "falling"; }
            case ObjectState::wallsliding: { return "wall_sliding"; }
            default: { break; }
        }
        return "undefined";
    }
}
