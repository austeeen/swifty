#ifndef UTIL_EXCEPTIONS_HPP
#define UTIL_EXCEPTIONS_HPP

#include <exception>
#include <memory>
#include <string>

#include "logging.hpp"

#define VERY_LARGE_NUM 5000
#define GETNAME(var) #var


class AABB;

bool __badVal(const int v);
bool __badVal(const AABB v);
bool __badVal(const std::string &v);
template <class BT, class MSK>
bool __badBit(const BT bt, const MSK mk) {
    return sizeof(mk)*8 <= (MSK) bt;
}

namespace ENGINESTATE {
    const int NO_STATE = 0x0;
    const int UNKNOWN  = 0x1;
    const int BUILD    = 0x2;
    const int STARTUP  = 0x3;
    const int RUN      = 0x4;
    const int EXIT     = 0x5;
}

struct SquareExceptionBase : public std::exception
{
    const char* what () const throw () { return what_str.c_str(); }
    std::string what_str;
};

struct NullPtrException : public SquareExceptionBase
{
    NullPtrException(const std::string obj_name) {
        what_str = "ptr '" + obj_name + "' == null but is expected to be initialized";
    }
};

struct NullPtrAccessException : public SquareExceptionBase
{
    NullPtrAccessException(const std::string obj_name) {
        what_str = "ptr '" + obj_name + "' == null but was attempted to be accessed";
    }
};

struct LoadFromFileException : public SquareExceptionBase
{
    LoadFromFileException(const std::string obj_name, const std::string fp) {
        what_str = "'" + obj_name + "' did not successfully load from file '" + fp + "'";
    }
};

struct BadValueException : public SquareExceptionBase
{
    BadValueException(const std::string where, const std::string obj_name) {
        what_str = "'" + where + "' has bad value in object '" + obj_name + "'";
    }
};

struct BadFileExtensionException : public SquareExceptionBase
{
    BadFileExtensionException(const std::string where, const std::string ext_name) {
        what_str = "'" + where + "' has bad file extension '" + ext_name + "'";
    }
};

template <class BIT, class MSK>
struct BitOverflowException : public SquareExceptionBase
{
    BitOverflowException(const BIT bt, const MSK mk) {
        what_str = "'" + std::to_string(bt) + "' >= '" + std::to_string(sizeof(mk) * 8) + "'";
    }
};

template <typename T>
inline void throwForNullPtr(T *obj, const std::string &obj_name) {
    if (obj == nullptr) throw NullPtrException(obj_name);
}

template <class T>
inline void throwForBadValue(const T &v, const char *what, const char *where) {
    if (__badVal(v)) throw BadValueException((std::string) where, (std::string) what);
}

template <class BIT, class MSK>
inline void throwForBitOverflow(const BIT bt, const MSK mk) {
    if (__badBit(bt, mk)) throw BitOverflowException(bt, mk);
}

template <class T>
inline void warnForBadValue(const T &v, const char *what, const char *where) {
    if (__badVal(v)) warn(where, "%s has bad value", what);
}



#endif // UTIL_EXCEPTIONS_HPP
