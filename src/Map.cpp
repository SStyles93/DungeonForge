#include "Map.hpp"

Map::Map(unsigned int width, unsigned int height)
    : width(width), height(height), tiles(width* height, 0)
{}

void Map::setTile(unsigned int x, unsigned int y, int value)
{
    if (x < width && y < height)
        tiles[y * width + x] = value;
}

int Map::getTile(unsigned int x, unsigned int y) const
{
    if (x < width && y < height)
        return tiles[y * width + x];
    return -1;
}

unsigned int Map::getWidth() const { return width; }
unsigned int Map::getHeight() const { return height; }


////DLL EXPORT
//
//PXP_DF_API Map* CreateMap(unsigned int width, unsigned int height)
//{
//    return new Map(width, height);
//}
//
//PXP_DF_API void DeleteMap(Map* instance)
//{
//    delete instance;
//}
//
//
//PXP_DF_API void SetTile(Map* instance, unsigned int x, unsigned int y, int value)
//{
//    if (instance == nullptr) return;
//    instance->setTile(x, y, value);
//}
//
//PXP_DF_API int GetTile(Map* instance, unsigned int x, unsigned int y)
//{
//    if (instance == nullptr) return 0;
//    else return instance->getTile(x, y);
//}
//
//
//PXP_DF_API int GetWidth(Map* instance)
//{
//    if (instance == nullptr) return -1;
//    else return instance->getWidth();
//}
//
//PXP_DF_API int GetHeight(Map* instance)
//{
//    if (instance == nullptr) return -1;
//    else return instance->getHeight();
//}