#include "logging.hpp"

void LOG::setlvl(enum LOG::loglevel& lvl, const int lvl_num)
{
    if (lvl_num < numlvls) {
        lvl = LOG::loglevel(lvl_num);
    } else {
        std::cout << "LOG::setlvl cannot set log level = " << lvl_num << std::endl;
        std::cout << "LOG::setlvl setting default log level [debug](4)" << std::endl;
        lvl = LOG::loglevel::dbg;
    }
}

const char* dbg_fmt  = "{ debug }(%s) ";
const char* msg_fmt  = "{  msg  }(%s) ";
const char* warn_fmt = "{ warn  }(%s) ";
const char* err_fmt  = "{ ERROR }(%s) ";

void __print(va_list& args, const char* pre_fmt, const char* where, const char* fmt)
{
    char *where_str = new char[MAX_STR_SIZE];
    sprintf(where_str, pre_fmt, where);

    char *what_str = new char[MAX_STR_SIZE];
    vsprintf(what_str, fmt, args);

    std::cout << where_str << what_str << std::endl;

    delete[] where_str;
    delete[] what_str;
}

void debug(const char *where, const char *fmt, ...)
{
    if (LOG::lvl < LOG::loglevel::dbg) {
        return;
    }
    va_list args;
    va_start(args, fmt);
    __print(args, dbg_fmt, where, fmt);
    va_end(args);
}

void msg(const char *where, const char *fmt, ...)
{
    if (LOG::lvl < LOG::loglevel::msg) {
        return;
    }
    va_list args;
    va_start(args, fmt);
    __print(args, msg_fmt, where, fmt);
    va_end(args);
}

void warn(const char *where, const char *fmt, ...)
{
    if (LOG::lvl < LOG::loglevel::wrn) {
        return;
    }
    va_list args;
    va_start(args, fmt);
    __print(args, warn_fmt, where, fmt);
    va_end(args);
}

void err(const char *where, const char *fmt, ...)
{
    if (LOG::lvl < LOG::loglevel::err) {
        return;
    }
    va_list args;
    va_start(args, fmt);
    __print(args, err_fmt, where, fmt);
    va_end(args);
}
