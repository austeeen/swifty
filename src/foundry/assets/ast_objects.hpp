#ifndef AST_OBJECTS_HPP
#define AST_OBJECTS_HPP

#include "asset_core.hpp"

struct ObjectAssetBase: Asset
{
    sf::Vector2i size, start_pos;
    std::string type;
    int x, y, w, h;
    int gid;
    std::map<const std::string, const std::string> properties;
    sf::Texture img_texture;
};

struct PlatformObjectAsset: ObjectAssetBase
{
    sf::IntRect position_rect, collision_rect;
    CollisionRect collider;
    int speed;
    int root_next_wp;
    Waypoint* root_waypoint;
    std::vector<PlatformObjectAsset> pieces;
    sf::VertexArray vertex_array;
    sf::RenderTexture* render_texture;
};

struct GameObjectAsset: public ObjectAssetBase
{
    const bool facing_right;
    const PhysicsCoeffs coeffs;
    std::map<ObjectState, std::shared_ptr<AnimRoll>> animation_rolls;
};

/*
struct ObjectAssetBase
{
    ObjectAssetBase(std::shared_ptr<TsxBaseObject> tsx_obj);

    sf::Vector2f start_pos;
    sf::Texture img_texture;
    const sf::Vector2i size;
};

struct GameObjectAsset: public ObjectAssetBase
{
    GameObjectAsset(std::shared_ptr<TileObject> tsx_obj);

    const std::string name;
    const bool facing_right;
    const PhysicsCoeffs coeffs;
    std::map<ObjectState, std::shared_ptr<AnimRoll>> animation_rolls;
};

struct PlatformObjectAsset: public ObjectAssetBase
{
    PlatformObjectAsset(std::shared_ptr<DynamicTiledObject> tsx_obj);

    const std::string name;
    const sf::FloatRect position_rect;
    const CollisionRect collider;
    const int speed;
    Waypoint* root_waypoint;
};



class TileObject
{
public:
    TileObject(const char* filepath);
    ~TileObject();
    void getProperties(rx::xml_node<>* node);
    void loadConfig(const char *cfg_fp);
    void addTile(rx::xml_node<>* node);
    void addRoll(std::shared_ptr<AnimRoll> roll, rx::xml_node<>* node);

    bool facing_right;
    sf::Texture img_texture;
    std::string img_src;
    int tilecount, columns, totaltiles;
    sf::Vector2i imagesize;
    sf::RenderStates render_states;
    std::map<const int, std::shared_ptr<TileFrame>> tile_tbl;
    std::map<ObjectState, std::shared_ptr<AnimRoll>> animation_rolls;
    std::string cfg_fp;
    PhysicsCoeffs pCoeffs;
};


class DynamicObjectAsset: public LayerObjectAsset
{
public:
    DynamicObjectAsset(rx::xml_node<>* node);
    ~DynamicObjectAsset();
    void add(rx::xml_node<>* node);
    void combinePieces(TileMap *map);
    void setWaypointTree(std::map<int, Waypoint>& all_waypoints);

    int speed;
    Waypoint* root_waypoint;
    rect position_rect;
    CollisionRect collider;
    sf::RenderTexture* render_texture;

private:
    rect collision_rect;
    std::vector<LayerObjectAsset> pieces;
    std::string type;
    int root_next_wp;
    sf::VertexArray vertex_array;
};
*/


#endif // AST_OBJECTS_HPP
