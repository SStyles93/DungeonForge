#include "Generator.hpp"
#include <random>

void Generator::Generate(Map& map)
{
    map.Clear();
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> distX(0, map.GetWidth());
    std::uniform_int_distribution<int> distY(0, map.GetHeight());

    // Randomly place rooms
    for (int i = 0; i < 50; ++i)
    {
        int x = distX(rng);
        int y = distY(rng);
        map.SetTile(x, y, TileType::Floor);
    }
}