#include "rsrc_tiled.hpp"

/*
std::ifstream JsonFileLoader::fs;
std::string JsonFileLoader::err_str;
Json::CharReaderBuilder JsonFileLoader::builder;
bool JsonFileLoader::load(const std::string &fp, Json::Value &root)
{
    fs.open(fp);
    if (!fs.is_open()) {
        SQ::err("JsonFileLoader::load", "could not open %s", fp.c_str());
        return false;
    }
    err_str = "";
    root.clear();
    Json::parseFromStream(builder, fs, &root, &err_str);

    if (fs.is_open()) {
        fs.close();
    }
    err_str = "";

    return true;
}
bool jsonRsrc::load(const std::string &fp)
{
    if (!JsonFileLoader::load(fp, root))
        return false;
    return true;
}
bool imgRsrc::load(const std::string &fp)
{
    if (!img_texture.loadFromFile(fp))
        return false;
    return true;
}
*/
