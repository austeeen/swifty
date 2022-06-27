#include "typedefs.hpp"

namespace out {
    const std::string toStr(const ObjectState s)
    {
        switch(s) {
            case ObjectState::idle: { return "idle"; }
            case ObjectState::running: { return "running"; }
            case ObjectState::jumping: { return "jumping"; }
            case ObjectState::falling: { return "falling"; }
            case ObjectState::healing: { return "healing"; }
            case ObjectState::damaged: { return "damaged"; }
            case ObjectState::dead: { return "dead"; }
            default: { break; }
        }
        return "undefined";
    }
}
PhysicsCoeffs::PhysicsCoeffs():
    mass(0), speed(0), maxvel(0), jump(0), gravity(0), damping(0)
{}
PhysicsCoeffs::PhysicsCoeffs(const PhysicsCoeffs& o):
    mass(o.mass), speed(o.speed), maxvel(o.maxvel), jump(o.jump), gravity(o.gravity), damping(o.damping)
{}
void PhysicsCoeffs::increase(const AsEnum cf)
{
    switch(cf) {
        case AsEnum::mass:    { mass    += MASS_UNIT;  break; }
        case AsEnum::speed:   { speed   += SPEED_UNIT; break; }
        case AsEnum::maxvel:  { maxvel  += VEL_UNIT;   break; }
        case AsEnum::jump:    { jump    += JUMP_UNIT;  break; }
        case AsEnum::gravity: { gravity += GRAV_UNIT;  break; }
        case AsEnum::damping: { damping += DAMP_UNIT;  break; }
    }
}
void PhysicsCoeffs::decrease(const AsEnum cf)
{
    switch(cf) {
        case AsEnum::mass:    { mass    -= MASS_UNIT;  break; }
        case AsEnum::speed:   { speed   -= SPEED_UNIT; break; }
        case AsEnum::maxvel:  { maxvel  -= VEL_UNIT;   break; }
        case AsEnum::jump:    { jump    -= JUMP_UNIT;  break; }
        case AsEnum::gravity: { gravity -= GRAV_UNIT;  break; }
        case AsEnum::damping: { damping -= DAMP_UNIT;  break; }
    }
}
std::ostream& operator<<(std::ostream& o, const PhysicsCoeffs& u)
{
    o << "{   mass   |  speed   |  maxvel  |   jump   | damping  | gravity  }\n";
    o << "{" << std::internal << std::setw(10) << u.mass
     << "|" << std::setw(10) << u.speed
     << "|" << std::setw(10) << u.maxvel
     << "|" << std::setw(10) << u.jump
     << "|" << std::setw(10) << u.damping
     << "|" << std::setw(10) << u.gravity
     << "}";
    return o;
}

Waypoint* Waypoint::setNext(Waypoint* n)
{
    this->next = n;
    this->next->prev = this;
    return n;
}
