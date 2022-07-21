#ifndef TILED_BYTES_HPP
#define TILED_BYTES_HPP

#include <map>
#include <vector>
#include <stdint.h>
#include <string>


/*************************************************************
 *                       TiledBytes                          *
 *    A lightweight API for Tiled Map Editor files in C++    *
 *              github.com/austeeen/tiledbytes               *
 *-----------------------------------------------------------*
 *    Austin Herman                                          *
 *    austinherman868@gmail.com                              *
 *************************************************************/



namespace tb
{

//------------------------------------------------------------------------------------------------//
//      ERROR CODES
//------------------------------------------------------------------------------------------------//

    namespace ERR
    {
        enum CODE : uint8_t {
            NONE = 0x0,
            UNDEFINED,
            FILE_LOAD_ERROR,
            FILE_NOT_FOUND,
            INVALID_LOAD_OBJECT,
            INVALID_EXTRACT_OBJECT,
            BAD_SEARCH_ROOT,
            NO_TILESET_FOUND,
            GID_OUT_OF_RANGE
        };
    } // namespace ERR

    extern uint8_t ERRCODE;

//----/ ERROR CODES /-----------------------------------------------------------------------------//


//------------------------------------------------------------------------------------------------//
//      OBJECTS AND TYPES
//------------------------------------------------------------------------------------------------//

    // Forward declarations

    struct Frame;
    struct Image;
    struct Layer;
        struct GroupedLayer;
        struct ObjectLayer;
        struct TileLayer;
    struct Rect;
        struct TextureRect;
            struct TileRect;
    struct Property;
    struct Tile;
    struct Tileset;
    struct Tmx;
    struct Tsx;
    struct Wangset;
    struct Wangtile;



    // Type declarations

    enum class FileType { Tsx, Tmx, Img };

    typedef std::vector<Layer>       LayerList;
    typedef std::vector<Rect>        RectList;
    typedef std::vector<TextureRect> TextureList;
    typedef std::vector<Tile>        TileList;
    typedef std::vector<Wangset>     WangsetList;
    typedef std::vector<Frame>       FrameList;

    typedef std::map<const std::string, const std::string> FileMap;
    typedef std::map<const FileType,    FileMap>           ResourceTable;
    typedef std::map<const std::string, const Property>    PropertyMap;
    typedef std::map<const int,         const Rect>        RectMap;
    typedef std::map<const int,         const TileRect>    TileMap;
    typedef std::map<const int,         const Tileset>     TilesetMap;
    typedef std::map<const int,         const Wangtile>    WangtileMap;
    typedef std::map<const int,         const FrameList>   AnimationMap;


    // Objects

    struct Frame {
        int tiled_id, duration;
    };

    struct Image {
        std::string source;
        int width, height;
    };

    struct Layer {
        virtual ~Layer() {};
        int id;
        std::string name;
        PropertyMap properties;
    };

    struct TileLayer: Layer {
        int width, height;
        TextureList tiles;
    };

    struct ObjectLayer: Layer {
        TileMap tilemap;
    };

    struct GroupedLayer: Layer {
        LayerList sublayers;
    };

    struct Property {
        std::string name, type, value;
    };

    struct Rect {
        int x, y, width, height;
    };

    struct TextureRect: Rect {
        int id, gid;
    };

    struct TileRect: TextureRect {
        std::string name, type;
        PropertyMap properties;
    };

    struct Tile {
        int id;
        std::string type;
        Rect position;
        TextureRect texture;
        RectList rects;
        PropertyMap properties;
        FrameList animation;
    };

    struct Tileset {
        int firstgid, tilewidth, tileheight, tilecount, columns;
        std::string name;
        Image image;
        TileList tiles;
        WangsetList wangsets;
        PropertyMap properties;
    };

    struct Tmx {
        std::string name;
        int width, height, tilewidth, tileheight;
        TilesetMap tilesets;
        LayerList layers;
        PropertyMap properties;
    };

    struct Tsx {
        int tilewidth, tileheight, tilecount, columns;
        std::string name;
        Image image;
        TileList tilelist;
        PropertyMap properties;
    };

    struct Wangset {
        std::string name, type;
        WangtileMap map;
    };

    struct Wangtile {
        int tileid, wangid;
        std::string wangid_str;
    };

//----/ OBJECTS AND TYPES /-----------------------------------------------------------------------//



//------------------------------------------------------------------------------------------------//
//      TILED PROJECT LOADING
//------------------------------------------------------------------------------------------------//

    void search(const std::string& filepath, ResourceTable& rsrc_tbl);

    template <typename T>
    void load(const std::string& filepath, T& dest_obj);

    template <typename T>
    T load(const std::string& filepath) {
        T dest_obj;
        load<T>(filepath, dest_obj);
        return dest_obj;
    }

    template <> void load(const std::string& filepath, Tmx& usr_tmx);
    template <> void load(const std::string& filepath, Tsx& usr_tsx);

//----/ TILED PROJECT LOADING /-------------------------------------------------------------------//



//------------------------------------------------------------------------------------------------//
//      SIMPLE UTILITY FUNCTIONS
//------------------------------------------------------------------------------------------------//

    bool getTileset(int& indx, tb::Tmx& tmx, const int gid);

    bool getTile(tb::Tile& dest, tb::Tileset& tileset, const int gid);

//----/ SIMPLE UTILITY FUNCTIONS /----------------------------------------------------------------//

} // namespace tb

#endif // TILED_BYTES_HPP
