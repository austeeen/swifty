#ifndef AST_CORE_HPP
#define AST_CORE_HPP

#include "../foundry_core.hpp"
#include "../tiled/all.hpp"

struct Asset
{
    Asset(const std::string& name): name(name) {};
    Asset(const int id): id(id) {};
    Asset(const int id, const std::string& name): id(id), name(name) {};
    Asset(const std::string& name, const int id): id(id), name(name) {};

    const int id = -1;
    const std::string name = "";

    const std::string str() const {
        std::stringstream ss;
        ss << "Asset[" << id << "][" <<  name << "]";
        return ss.str();
    };
};


#endif // AST_CORE_HPP
