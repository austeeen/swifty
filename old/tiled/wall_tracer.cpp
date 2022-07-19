#include "wall_tracer.hpp"

Tracer::Tracer(rx::xml_node<> *node)
{}
void Tracer::setUpWangset(rx::xml_node<> *node)
{
    rx::xml_node<> *wang_node = node->first_node("wangset");
    while(wang_node) {
        if (std::string(wang_node->name()) == "wangtile") {
            const char* wang_id = attr<std::string>(wang_node, "wangid").c_str();
            int wang_indx = 0;
            for (int i = 0; i < 4; i ++) {
                if (wang_id[i * 4] == HASEDGE) {
                    wang_indx |= 1 << i;
                }
            }
            if (wang_indx) {
                tile_to_wangset[attr<int>(wang_node, "tileid")] = wang_indx;
            }
        }
    }
}
void Tracer::traceGidStr(const std::string& gid_str, const sf::Vector2i& size)
{
    const int bw = size.x;
    const int bh = size.y;

    std::vector<int> allgids;
    split(gid_str, ',', allgids);

    for (size_t i = 0; i < allgids.size(); i ++) {
        if (allgids[i] == 0) {
            alltiles.push_back(nullptr);
        } else {
            alltiles.push_back(new Tile(allgids[i], i % bw, i / bw));
        }
    }

    for (size_t i = 0; i < alltiles.size(); i ++) {
        Tile *t = alltiles[i];
        if (t->y > 0)
            t->setNeighbor(Dir4::up,    alltiles[i - bw]);
        if (t->y < (bh - 1))
            t->setNeighbor(Dir4::down,  alltiles[i + bw]);
        if (t->x > 0)
            t->setNeighbor(Dir4::left,  alltiles[i - 1]);
        if (t->x < (bw - 1))
            t->setNeighbor(Dir4::right, alltiles[i + 1]);
    }
}
void Tracer::traceAll()
{

}