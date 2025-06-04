#include "DungeonGenerator.hpp"
#include <random>

void DungeonGenerator::Generate(DungeonMap& map)
{
    map.Clear();
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> distX(1, map.GetWidth() - 2);
    std::uniform_int_distribution<int> distY(1, map.GetHeight() - 2);

    // Randomly place rooms
    for (int i = 0; i < 50; ++i)
    {
        int x = distX(rng);
        int y = distY(rng);
        map.SetTile(x, y, TileType::Floor);
    }
}