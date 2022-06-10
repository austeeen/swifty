#ifndef FACTORY_RSRC_HPP
#define FACTORY_RSRC_HPP

/*
#include "common.hpp"
#include "resources.hpp"
#include <filesystem>

class ResourceFactory
{
public:
    ResourceFactory(const std::string& meta_cfg_fp);
    ~ResourceFactory();
    void build();
    void loadScene(const std::string& key, const std::string &fp);
    void loadTable(const std::string& key, const std::string &fp);
    void loadImage(const std::string& key, const std::string &fp, const int img_cols);
    void getScene(Json::Value &root, const std::string& key);
    void getTable(Json::Value &root, const std::string& key);
    void getImage(sf::Texture &img_txtr, const std::string& key);
    void getImage(sf::Texture &img_txtr, int &img_cols, const std::string& key);
    SQ::Font* getFont();
private:
    rsrc* __getRsrc(const std::string& fp);

    template <class R>
    void __cacheRsrc(std::map<std::string, R> &cache, const std::string& key, const std::string& fp);

    const std::string meta_cfg_fp;
    std::map<std::string, jsonRsrc> scene_cache;
    std::map<std::string, jsonRsrc> table_cache;
    std::map<std::string, imgRsrc> image_cache;
    SQ::Font* __font;
};
*/

#endif // FACTORY_RSRC_HPP
