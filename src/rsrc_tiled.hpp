#ifndef FCT_RSRCS_HPP
#define FCT_RSRCS_HPP
/*
#include "rapidxml/rapidxml.hpp"
#include "common.hpp"

class XML
{
public:
    static std::ifstream fs;
    static std::string err_str;
    static Json::CharReaderBuilder builder;
    static bool load(const std::string &fp, Json::Value &root);
};

struct rsrc {
    virtual bool load(const std::string &fp) = 0;
    virtual ~rsrc() {};
};

struct jsonRsrc: public rsrc {
    bool load(const std::string &fp) override;
    Json::Value root;
};

struct imgRsrc: public rsrc {
    bool load(const std::string &fp) override;
    int img_cols;
    sf::Texture img_texture;
};
*/

#endif // FCT_RSRCS_HPP
