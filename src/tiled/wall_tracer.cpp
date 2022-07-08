#include "wall_tracer.hpp"

Tracer::Tracer(rx::xml_node<> *node)
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
                wangset[attr<int>(wang_node, "tileid")] = wang_indx;
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
        const int tx = i % bw;
        const int ty = i / bw;
        
        Tile *t = allgids[i];
        if (t->crd.y > 0)
            t->setNeighbor(bt::dir4::up,    alltiles[i - bw]);
        if (t->crd.y < (bh - 1))
            t->setNeighbor(bt::dir4::down,  alltiles[i + bw]);
        if (t->crd.x > 0)
            t->setNeighbor(bt::dir4::left,  alltiles[i - 1]);
        if (t->crd.x < (bw - 1))
            t->setNeighbor(bt::dir4::right, alltiles[i + 1]);
    }}
