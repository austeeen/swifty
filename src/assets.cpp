#include "assets.hpp"

GameObjectAsset::GameObjectAsset(const ObjectConfig& cfg) :
speed(cfg.speed),
mass(cfg.mass),
max_x_vel(cfg.max_x_vel),
jump_power(cfg.jump_power),
acl_gravity(cfg.acl_gravity),
damping(cfg.damping)
{}
