#ifndef LOGGING_HPP
#define LOGGING_HPP

#include <cstdarg>
#include <cstdio>
#include <iostream>

#include "typedefs.hpp"

#define MAX_STR_SIZE 1024

class Logger {
public:
    enum loglevel { err = 0, wrn, msg, dbg };
    static loglevel lvl;
    static const int numlvls = 4;

    static void setlvl(const int lvl_num);
};

namespace out {
    const std::string toStr(const ObjectState s);

    void debug(const char *where, const char *fmt, ...);
    inline void debug(const char* str) { debug(str, ""); }

    void msg(const char *where, const char *fmt, ...);
    inline void msg(const char* str) { msg(str, ""); }

    void warn(const char *where, const char *fmt, ...);
    inline void warn(const char* str) { warn(str, ""); }

    void err(const char *where, const char *fmt, ...);
    inline void err(const char* str) { err(str, ""); }
}

#endif // LOGGING_HPP
