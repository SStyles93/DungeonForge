#include "Generator.hpp"
#include <cstdlib>  // for std::rand
#include <algorithm>
#include <cmath>

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

void Generator::BSP(Map& map)
{
    // Fill map with walls
    for (unsigned int y = 0; y < map.getHeight(); ++y)
        for (unsigned int x = 0; x < map.getWidth(); ++x)
            map.setTile(x, y, 1);

    std::vector<Rect> spaces;
    spaces.push_back({ 1, 1, (int)map.getWidth() - 2, (int)map.getHeight() - 2 });

    int maxLeafSize = 20;
    splitSpace(spaces, maxLeafSize);

    std::vector<sf::Vector2i> roomCenters;

    for (const Rect& space : spaces)
    {
        // Room size
        int roomWidth = 4 + std::rand() % (space.width);
        int roomHeight = 4 + std::rand() % (space.height);

        int roomX = space.x + std::rand() % (space.width);
        int roomY = space.y + std::rand() % (space.height);

        Rect room = { roomX, roomY, roomWidth, roomHeight };
        createRoom(map, room);

        // Store center
        roomCenters.push_back({ roomX + roomWidth / 2, roomY + roomHeight / 2 });
    }

    // Connect rooms by chaining center points
    for (size_t i = 1; i < roomCenters.size(); ++i)
        connectRooms(map, roomCenters[i - 1], roomCenters[i]);
}

void Generator::splitSpace(std::vector<Rect>& spaces, int maxLeafSize)
{
    bool didSplit = true;

    while (didSplit)
    {
        didSplit = false;
        std::vector<Rect> newSpaces;

        for (const Rect& space : spaces)
        {
            bool splitH = std::rand() % 2;
            if (space.width > space.height && (float)space.width / space.height >= 1.25f)
                splitH = false;
            else if (space.height > space.width && (float)space.height / space.width >= 1.25f)
                splitH = true;

            if ((splitH && space.height <= maxLeafSize) ||
                (!splitH && space.width <= maxLeafSize))
            {
                newSpaces.push_back(space);
                continue;
            }

            if (splitH)
            {
                int split = 4 + std::rand() % (space.height - 8);
                newSpaces.push_back({ space.x, space.y, space.width, split });
                newSpaces.push_back({ space.x, space.y + split, space.width, space.height - split });
            }
            else
            {
                int split = 4 + std::rand() % (space.width - 8);
                newSpaces.push_back({ space.x, space.y, split, space.height });
                newSpaces.push_back({ space.x + split, space.y, space.width - split, space.height });
            }

            didSplit = true;
        }

        spaces = newSpaces;
    }
}

void Generator::createRoom(Map& map, const Rect& room)
{
    for (int y = room.y; y < room.y + room.height; ++y)
    {
        for (int x = room.x; x < room.x + room.width; ++x)
        {
            map.setTile(x, y, 0);
        }
    }
}

void Generator::connectRooms(Map& map, const sf::Vector2i& pointA, const sf::Vector2i& pointB)
{
    sf::Vector2i current = pointA;

    while (current.x != pointB.x)
    {
        map.setTile(current.x, current.y, 0);
        current.x += (pointB.x > current.x) ? 1 : -1;
    }

    while (current.y != pointB.y)
    {
        map.setTile(current.x, current.y, 0);
        current.y += (pointB.y > current.y) ? 1 : -1;
    }
}
