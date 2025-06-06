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

unsigned int Map::GetWidth() const { return width; }
unsigned int Map::GetHeight() const { return height; }
