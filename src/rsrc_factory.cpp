#include "rsrc_factory.hpp"

/*
ResourceFactory::ResourceFactory(const std::string& meta_cfg_fp):
 meta_cfg_fp(meta_cfg_fp), __font(new SQ::Font())
{}
ResourceFactory::~ResourceFactory()
{
    SQ::destroy(__font);
    scene_cache.clear();
    table_cache.clear();
    image_cache.clear();
}
void ResourceFactory::build()
{
    jsonRsrc* config = static_cast<jsonRsrc*>(__getRsrc(meta_cfg_fp));
    if (!config->load(meta_cfg_fp)) {
        SQ::err("ResourceFactory::build", "failed to load %s", meta_cfg_fp.c_str());
        delete config;
        return;
    }
    Json::Value rsrc_paths = config->root["resource_paths"];

    Json::Value scns = rsrc_paths["scn"];
    for (Json::Value::const_iterator itr = scns.begin(); itr != scns.end(); itr++) {
        this->loadScene(itr.name(), itr->asString());
    }

    Json::Value tbls = rsrc_paths["tbl"];
    for (Json::Value::const_iterator itr = tbls.begin(); itr != tbls.end(); itr++) {
        this->loadTable(itr.name(), itr->asString());
    }

    Json::Value imgs = rsrc_paths["img"];
    for (Json::Value::const_iterator itr = imgs.begin(); itr != imgs.end(); itr++) {
        Json::Value img_root = *itr;
        this->loadImage(itr.name(), img_root["img_fp"].asString(), img_root["img_cols"].asInt());
    }

    this->__font->load(rsrc_paths["font"].asString());

    delete config;
}
void ResourceFactory::loadScene(const std::string& key, const std::string &fp)
{
    __cacheRsrc(scene_cache, key, fp);
}
void ResourceFactory::loadTable(const std::string& key, const std::string &fp)
{
    __cacheRsrc(table_cache, key, fp);
}
void ResourceFactory::loadImage(const std::string& key, const std::string &fp, const int img_cols)
{
    __cacheRsrc(image_cache, key, fp);
    image_cache[key].img_cols = img_cols;
}
void ResourceFactory::getScene(Json::Value &root, const std::string& key)
{
    root = scene_cache.at(key).root;
}
void ResourceFactory::getTable(Json::Value &root, const std::string& key)
{
    root = table_cache.at(key).root;
}
void ResourceFactory::getImage(sf::Texture &img_txtr, const std::string& key)
{
    img_txtr = image_cache.at(key).img_texture;
}
void ResourceFactory::getImage(sf::Texture &img_txtr, int &img_cols, const std::string& key)
{
    img_txtr = image_cache.at(key).img_texture;
    img_cols = image_cache.at(key).img_cols;
}
SQ::Font* ResourceFactory::getFont()
{
    return this->__font;
}
rsrc* ResourceFactory::__getRsrc(const std::string& fp)
{
    std::string ext = std::filesystem::path(fp).extension();
    if (ext == ".png")
        return new imgRsrc();
    else if (ext == ".json")
    {
        // all jsons load the same for now so essentially just checking for "valid" sub extension
        std::string stem = std::filesystem::path(fp).stem();
        ext = std::filesystem::path(stem).extension();
        if (ext == ".scn")
            return new jsonRsrc();
        else if (ext == ".tbl")
            return new jsonRsrc();
        else if (ext == ".cfg")
            return new jsonRsrc();
        else
            SQ::err("ResourceFactory::__getRsrc", "unrecognized json sub-extension %s", ext.c_str());
    } else
        SQ::err("ResourceFactory::__getRsrc", "unrecognized extension %s", ext.c_str());
    throw SQ::BadFileExtensionException("ResourceFactory::getRsrc", fp);
}
template <class R>
void ResourceFactory::__cacheRsrc(std::map<std::string, R> &cache, const std::string& key, const std::string& fp)
{
    cache[key] = R();
    if (!cache[key].load(fp))
        SQ::err("ResourceFactory::__cacheRsrc", "failed to load %s", key.c_str());
}
*/
