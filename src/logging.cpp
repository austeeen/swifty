#include "logging.hpp"

Logger::loglevel Logger::lvl;

void Logger::setlvl(const int lvl_num) {
    if (lvl_num < numlvls) {
        lvl = Logger::loglevel(lvl_num);
    } else {
        std::cout << "Logger::setlvl cannot set log level = " << lvl_num << std::endl;
        std::cout << "Logger::setlvl setting default log level [debug](4)" << std::endl;
        lvl = Logger::loglevel::dbg;
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

namespace out 
{
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

    void debug(const char *where, const char *fmt, ...)
    {
        if (Logger::lvl < Logger::loglevel::dbg) {
            return;
        }
        va_list args;
        va_start(args, fmt);
        __print(args, dbg_fmt, where, fmt);
        va_end(args);
    }

    void msg(const char *where, const char *fmt, ...)
    {
        if (Logger::lvl < Logger::loglevel::msg) {
            return;
        }
        va_list args;
        va_start(args, fmt);
        __print(args, msg_fmt, where, fmt);
        va_end(args);
    }

    void warn(const char *where, const char *fmt, ...)
    {
        if (Logger::lvl < Logger::loglevel::wrn) {
            return;
        }
        va_list args;
        va_start(args, fmt);
        __print(args, warn_fmt, where, fmt);
        va_end(args);
    }

    void err(const char *where, const char *fmt, ...)
    {
        if (Logger::lvl < Logger::loglevel::err) {
            return;
        }
        va_list args;
        va_start(args, fmt);
        __print(args, err_fmt, where, fmt);
        va_end(args);
    }
}