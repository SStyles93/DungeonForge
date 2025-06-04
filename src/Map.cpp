#include "Map.hpp"

Map::Map(int width, int height)
    : m_Width(width), m_Height(height), m_Tiles(width* height, TileType::Empty)
{}

void Map::Clear()
{
    std::fill(m_Tiles.begin(), m_Tiles.end(), TileType::Empty);
}

int Map::GetWidth() const { return m_Width; }
int Map::GetHeight() const { return m_Height; }

TileType Map::GetTile(int x, int y) const
{
    if (x < 0 || x >= m_Width || y < 0 || y >= m_Height)
        return TileType::Empty;
    return m_Tiles[y * m_Width + x];
}

void Map::SetTile(int x, int y, TileType type)
{
    if (x < 0 || x >= m_Width || y < 0 || y >= m_Height)
        return;
    m_Tiles[y * m_Width + x] = type;
}