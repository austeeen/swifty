#include "typedefs.hpp"
#include "utils/utils.hpp"


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
        case AsEnum::mass:    { mass    -= MASS_UNIT;  bound_low(mass,    1); break; }
        case AsEnum::speed:   { speed   -= SPEED_UNIT; bound_low(speed,   1); break; }
        case AsEnum::maxvel:  { maxvel  -= VEL_UNIT;   bound_low(maxvel,  1); break; }
        case AsEnum::jump:    { jump    -= JUMP_UNIT;  bound_low(jump,    1); break; }
        case AsEnum::gravity: { gravity -= GRAV_UNIT;  bound_low(gravity, 1); break; }
        case AsEnum::damping: { damping -= DAMP_UNIT;  bound_low(damping, 1); break; }
    }
}
const std::string PhysicsCoeffs::asStr() const {
    std::stringstream ss;
    ss << "{   mass   |  speed   |  maxvel  |   jump   | damping  | gravity  }\n";
    ss << "{" << std::internal 
      << std::setw(10) << this->mass
      << "|" << std::setw(10) << this->speed
      << "|" << std::setw(10) << this->maxvel
      << "|" << std::setw(10) << this->jump
      << "|" << std::setw(10) << this->damping
      << "|" << std::setw(10) << this->gravity
      << "}";
    return ss.str();
}
std::ostream& operator<<(std::ostream& o, const PhysicsCoeffs& u)
{
    o << u.asStr();
    return o;
}

Waypoint* Waypoint::setNext(Waypoint* n)
{
    this->next = n;
    this->next->prev = this;
    return n;
}
