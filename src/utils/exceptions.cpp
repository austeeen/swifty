#include "exceptions.hpp"
#include "math/aabb.hpp"

bool __badVal(const int v) { return v == 0; }
bool __badVal(const AABB v) { return (v.width == 0 && v.height == 0) || (v.width > VERY_LARGE_NUM || v.height > VERY_LARGE_NUM); }
bool __badVal(const std::string &v) { return v == ""; }
