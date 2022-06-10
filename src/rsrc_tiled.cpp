#include "rsrc_tiled.hpp"

void readFromXmlFile(rx::xml_document<> doc)
{
  rx::xml_node<> *pRoot = doc.first_node();

  for(rx::xml_node<> *pNode=pRoot->first_node("node"); pNode; pNode=pNode->next_sibling())
  {
    // This loop will walk you through two nodes:
    // node attribute="0" and then node attribute="1"
    // Do something here
  }

  // access node 'node' and then node attribute 'attribute' and its value
  rx::xml_node<> *pNode = pRoot->first_node("node");
  rx::xml_attribute<> *pAttr = pNode->first_attribute("attribute");
  // save values from the document (reallocation necessary for when doc is
  // closed or goes out of scope)
  std::string strValue = pAttr->value();
  int nValue = atoi(pAttr->value());

  // create char string from nValue, and output it to the doc as a new attribute
  char pbuff[32];
  std::sprintf(pbuff, "%d", nValue);
  pAttr->value(doc.allocate_string(pbuff));
  pNode->append_attribute(doc.allocate_attribute("new_attribute"));
}

/******************************************************************************/

void openXmlFile(const char *filepath, rx::xml_document<>* doc)
{
  std::ifstream file(filepath);
  std::stringstream buffer;
  buffer << file.rdbuf();
  file.close();
  std::string content(buffer.str());
  doc->parse<0>(&content[0]);
}

void val(std::string& value, rx::xml_node<> *node)
{
  value = node->value();
}
void attr(int &dst, const char* attr_name, rx::xml_node<> *node)
{
  dst = std::atoi(node->first_attribute(attr_name)->value());
}
void attr(std::string &dst, const char* attr_name, rx::xml_node<> *node)
{
  dst = std::string(node->first_attribute(attr_name)->value());
}

/******************************************************************************/

LayerObject::LayerObject(rx::xml_node<> *node)
{

}

MapLayer::MapLayer(rx::xml_node<> *node)
{

}
TileLayer::TileLayer(rx::xml_node<> *node):
 MapLayer(node)
{

}
ObjectGroup::ObjectGroup(rx::xml_node<> *node):
 MapLayer(node)
{

}

TileSet::TileSet(rx::xml_node<> *node)
{

}

TileMap::TileMap(const char* filepath)
{
  doc = new rx::xml_document<>();
  openXmlFile(filepath, doc);
  rx::xml_node<> *root = doc->first_node();
  rx::xml_node<> *map = root->first_node("map");
  attr(mapsize.x, "width", map);
  attr(mapsize.y, "height", map);
  attr(tilesize.x, "tilewidth", map);
  attr(tilesize.y, "tileheight", map);

  rx::xml_node<> *node = map->first_node();
  while (node) {
    std::string name;
    attr(name, "name", node);
    std::string type = std::string(node->name());
    if (type == "tileset") {
      tilesets[name] = TileSet(node);
    }
    else if (type == "layer") {
      layers[name] = TileLayer(node);
    }
    else if (type == "objectgroup") {
      layers[name] = ObjectGroup(node);
    }
    node = node->next_sibling();
  }

}

/******************************************************************************/
