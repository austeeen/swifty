#ifndef UTIL_LOGGING_HPP
#define UTIL_LOGGING_HPP

#include <cstdarg>
#include <cstdio>
#include <iostream>

#define MAX_STR_SIZE 1024

namespace LOG {
    enum loglevel { err = 0, wrn, msg, dbg };
    void setlvl(enum loglevel& lvl, const int lvl_num);
    const int numlvls = 4;
    extern loglevel lvl;
}

void debug(const char *where, const char *fmt, ...);
void msg(const char *where, const char *fmt, ...);
void warn(const char *where, const char *fmt, ...);
void err(const char *where, const char *fmt, ...);


#endif // UTIL_LOGGING_HPP
