#pragma once
#include <vector>

enum class TileType {
    Empty,
    Floor,
    Wall
};

class Map 
{
public:
    //Ctor
    Map(int width, int height);

    void Clear();
    int GetWidth() const;
    int GetHeight() const;
    TileType GetTile(int x, int y) const;
    void SetTile(int x, int y, TileType type);

private:
    int m_Width;
    int m_Height;
    std::vector<TileType> m_Tiles;
};
