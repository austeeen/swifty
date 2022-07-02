# file to use-able game asset

input file | tiled resource | asset
-----------------------------------------
   .tmx    |    TileMap     | SceneAsset
   .tsx    |

   
    TileMap
        - TileSet
        - TileLayer
        - ObjectLayer
    TsxObject

output asset:
    SceneAsset
        - TileLayerAsset
        - BoundaryLayerAsset
        - PlatformLayerAsset
            - map<string, PlatformObjectAsset>
        - GameObjectLayerAsset
            - map<string, GameObjectAsset>
