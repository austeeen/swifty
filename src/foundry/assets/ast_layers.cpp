#include "ast_layers.hpp"

LayerAssetBase::LayerAssetBase(Layer* lyr_res):
    Asset(lyr_res->name, lyr_res->id), r_order(lyr_res->id), type(lyr_res->type)
{

}

TileLayerAsset::TileLayerAsset(TileLayer* lyr_res):
    LayerAssetBase(lyr_res)
{

}

BoundaryLayerAsset::BoundaryLayerAsset(ObjectLayer* lyr_res):
    LayerAssetBase(lyr_res)
{

}

PlatformLayerAsset::PlatformLayerAsset(ObjectLayer* lyr_res):
    LayerAssetBase(lyr_res)
{

}

GameObjectLayerAsset::GameObjectLayerAsset(ObjectLayer* lyr_res):
    LayerAssetBase(lyr_res)
{

}

/*
INITIALIZING ANIMATION ROLLS
std::string anim_roll = attr_if<std::string>(node, "type");
if (anim_roll == "idle") {
    animation_rolls[ObjectState::idle] = std::make_shared<AnimRoll>();
} else if (anim_roll == "running") {
    animation_rolls[ObjectState::running] = std::make_shared<AnimRoll>();
} else if (anim_roll == "jumping") {
    animation_rolls[ObjectState::jumping] = std::make_shared<AnimRoll>();
} else if (anim_roll == "falling") {
    animation_rolls[ObjectState::falling] = std::make_shared<AnimRoll>();
} else if (anim_roll == "healing") {
    animation_rolls[ObjectState::healing] = std::make_shared<AnimRoll>();
} else if (anim_roll == "damaged") {
    animation_rolls[ObjectState::damaged] = std::make_shared<AnimRoll>();
} else if (anim_roll == "dead") {
    animation_rolls[ObjectState::dead] = std::make_shared<AnimRoll>();
}

COMBINING ANIMATION FRAMES TO CREATE A ROLL
node = ts_node->first_node();
while(node != nullptr) {
    std::string anim_roll = attr_if<std::string>(node, "type");
    if (anim_roll == "idle") {
        addRoll(animation_rolls[ObjectState::idle], node);
    } else if (anim_roll == "running") {
        addRoll(animation_rolls[ObjectState::running], node);
    } else if (anim_roll == "jumping") {
        addRoll(animation_rolls[ObjectState::jumping], node);
    } else if (anim_roll == "falling") {
        addRoll(animation_rolls[ObjectState::falling], node);
    } else if (anim_roll == "healing") {
        addRoll(animation_rolls[ObjectState::healing], node);
    } else if (anim_roll == "damaged") {
        addRoll(animation_rolls[ObjectState::damaged], node);
    } else if (anim_roll == "dead") {
        addRoll(animation_rolls[ObjectState::dead], node);
    }
    node = node->next_sibling();

addRoll()
    rx::xml_node<> *frame_node = tile_node->first_node("animation")->first_node("frame");
    while(frame_node) {
        int gid = attr<int>(frame_entry, "tileid");
        std::shared_ptr<TileFrame> frame = tile_tbl[gid];
        frame->duration = attr<float>(frame_entry, "duration") * 0.001f;
        roll->frames.push_back(frame);
        frame_entry = frame_entry->next_sibling();
    }
}

ROLL PROPERTY PROCESSING
rx::xml_node<> *prp = node->first_node("properties")->first_node("property");
while(prp != nullptr) {
    std::string prp_name = attr<std::string>(prp, "name");
    if (prp_name == "end_early") {
        roll->end_early_frame = attr_if<int>(prp, "value");
    } else if (prp_name == "hold_last") {
        roll->hold_last_frame = attr_if<bool>(prp, "value");
    } else if (prp_name == "one_shot") {
        roll->one_shot = attr_if<bool>(prp, "value");
    }
    prp = prp->next_sibling();
}



FACING STUFF
if (facing_right) {
    printf("%s is facing right\n", name.c_str());
} else {
    printf("%s is facing left\n", name.c_str());
}

COLLISION RECT STUFF

ColliderType ct = ColliderType::generic;
if (type == "body") {
    ct = ColliderType::body;
}

float col_x = std::round(attr<float>(c_rects, "x"));
float col_y = std::round(attr<float>(c_rects, "y"));
tile->collision_rects.push_back({
    sf::Vector2f(col_x, col_y),
    sf::FloatRect(col_x, col_y,
        std::round(attr<float>(c_rects, "width")), std::round(attr<float>(c_rects, "height"))),
    ct
});
*/
