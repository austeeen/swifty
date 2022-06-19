#ifndef IO_CORE_HPP
#define IO_CORE_HPP

#include "common.hpp"

namespace joy
{
    const int SFML_MAX_JOYS = 8;

    bool connected_joys(std::vector<int> &cons);

    typedef uint8_t button;

    namespace snes {
        const button X = 0;
        const button A = 1;
        const button B = 2;
        const button Y = 3;
        const button L = 4;
        const button R = 5;
        const button SL = 8;
        const button ST = 9;
        const button NONE = 10;
    }
}

namespace io
{
    const int NSTATES = 4;
    typedef uint8_t state;
    const state up_s = 0;
    const state released_s = 1;
    const state pressed_s = 2;
    const state down_s = 3;

    const int NBINDS = 9;
    typedef uint8_t binding;
    const binding left = 0;
    const binding right = 1;
    const binding down = 2;
    const binding up = 3;
    const binding select = 4;
    const binding back = 5;
    const binding menu = 6;
    const binding quit = 7;
    const binding none = 8;

    extern const char* str_bindings[];
    extern const char* str_states[];

}


#endif // IO_CORE_HPP
