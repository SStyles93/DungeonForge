#pragma once
#include <vector>

enum class TileType {
    Empty,
    Floor,
    Wall
};

class DungeonMap {
public:
    //Ctor
    DungeonMap();
    DungeonMap(int width, int height);
    //Dtor
    ~DungeonMap();
    //Copy Ctor
    DungeonMap(const DungeonMap& other);
    //Move Ctor
    DungeonMap(DungeonMap&& other);
    //Copy assign
    DungeonMap& operator=(const DungeonMap& other)
    {
        return *this = DungeonMap(other);
    }
    //Move assign
    DungeonMap& operator=(DungeonMap&& other) 
    {
        //std::swap(val, other.val)
        //return *this;
    }

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
