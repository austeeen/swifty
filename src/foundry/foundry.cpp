#include "foundry.hpp"

void ResourceTable::loadFileList(const std::vector<std::string>& file_list)
{
    for (auto& fp : file_list) {
        std::filesystem::path filepath(fp);
        if (filepath.extension() == ".tmx") {
            tmx[std::string(filepath.stem())] = new TileMap(fp.c_str());
        } else if (filepath.extension() == ".tsx") {
            tsx[std::string(filepath.stem())] = new TsxObject(fp.c_str());
        }
    }

    for (auto& [name, map] : tmx) {
        map->process();
    }
    for (auto& [name, obj] : tsx) {
        obj->process();
    }
}

Foundry::Foundry()
{
    res_tbl.loadFileList(tiled_files);
}
Foundry::~Foundry()
{
    // todo clean up tables
}
SceneAsset* Foundry::loadScene(const std::string& scene_name)
{
    if (loaded_scenes.count(scene_name) == 0) {
        loaded_scenes[scene_name] = createNewScene(scene_name);
    }
    return loaded_scenes[scene_name];
}
SceneAsset* Foundry::createNewScene(const std::string& map_name)
{
    SceneAsset* scn_ast = new SceneAsset(res_tbl.tmx[map_name]);
    scn_ast->build(this);
    return scn_ast;
}
