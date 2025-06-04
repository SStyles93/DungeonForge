#include "DungeonMap.hpp"

DungeonMap::DungeonMap(int width, int height)
    : m_Width(width), m_Height(height), m_Tiles(width* height, TileType::Empty)
{}

void DungeonMap::Clear()
{
    std::fill(m_Tiles.begin(), m_Tiles.end(), TileType::Empty);
}

int DungeonMap::GetWidth() const { return m_Width; }
int DungeonMap::GetHeight() const { return m_Height; }

TileType DungeonMap::GetTile(int x, int y) const
{
    if (x < 0 || x >= m_Width || y < 0 || y >= m_Height)
        return TileType::Empty;
    return m_Tiles[y * m_Width + x];
}

void DungeonMap::SetTile(int x, int y, TileType type)
{
    if (x < 0 || x >= m_Width || y < 0 || y >= m_Height)
        return;
    m_Tiles[y * m_Width + x] = type;
}