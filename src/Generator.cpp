#include "Generator.hpp"
#include <cstdlib>  // for std::rand

void Generator::Perlin(Map& map)
{
    for (unsigned int y = 0; y < map.getHeight(); ++y)
    {
        for (unsigned int x = 0; x < map.getWidth(); ++x)
        {
            // Randomly assign 0 (floor) or 1 (wall)
            int tileValue = std::rand() % 2;
            map.setTile(x, y, tileValue);
        }
    }
}

void Generator::DrunkardsWalk(Map& map)
{
    // Fill map with walls (1)
    for (unsigned int y = 0; y < map.getHeight(); ++y)
        for (unsigned int x = 0; x < map.getWidth(); ++x)
            map.setTile(x, y, 1);

    unsigned int floorCount = 0;
    unsigned int targetFloorCount = (map.getWidth() * map.getHeight()) * 0.4f;

    // Start in the center
    int x = map.getWidth() / 2;
    int y = map.getHeight() / 2;

    map.setTile(x, y, 0);
    floorCount++;

    while (floorCount < targetFloorCount)
    {
        // Random move: 0=left, 1=right, 2=up, 3=down
        int dir = std::rand() % 4;

        switch (dir)
        {
            case 0: if (x > 1) x--; break;
            case 1: if (x < (int)map.getWidth() - 2) x++; break;
            case 2: if (y > 1) y--; break;
            case 3: if (y < (int)map.getHeight() - 2) y++; break;
        }

        // If cell was a wall, turn it to floor and increment
        if (map.getTile(x, y) == 1)
        {
            map.setTile(x, y, 0);
            floorCount++;
        }
    }
}
