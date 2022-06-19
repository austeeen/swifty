#ifndef UTIL_MATH_H
#define UTIL_MATH_H

#include <cstdint>
#include "aabb.hpp"

const int X = 0;
const int Y = 1;
typedef const uint8_t dir;
enum dir4: dir { up, right, down, left, none };
enum dir8: dir { ul, u, ur, r, dr, d, dl, l };


#endif // UTIL_MATH_H
