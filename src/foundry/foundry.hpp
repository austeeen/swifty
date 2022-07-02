#ifndef FND_FOUNDRY_HPP
#define FND_FOUNDRY_HPP

#include "foundry_core.hpp"
#include "tiled/all.hpp"
#include "assets/all.hpp"

struct ResourceTable
{
    void loadFileList(const std::vector<std::string>& file_list);
    std::map<std::string, TileMap*> tmx;
    std::map<std::string, TsxObject*> tsx;
};

class Foundry
{
public:
    Foundry();
    ~Foundry();
    SceneAsset* loadScene(const std::string& scene_name);

    const std::vector<std::string> tiled_files = {
        "res/new_basic_level.tmx",
        "res/cat_new.tsx",
        "res/spider.tsx"
    };

private:
    SceneAsset* createNewScene(const std::string& map_name);

    ResourceTable res_tbl;
    std::map<std::string, SceneAsset*> loaded_scenes;
};

#endif // FND_FOUNDRY_HPP
