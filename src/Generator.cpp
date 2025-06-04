#include "Generator.hpp"


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



void Generator::CellularAutomata(Map& map, int fillProbability, int iterations)
{
    // Fill map with walls (default)
    for (unsigned int y = 0; y < map.getHeight(); ++y)
        for (unsigned int x = 0; x < map.getWidth(); ++x)
            map.setTile(x, y, 1);

    unsigned int width = map.getWidth();
    unsigned int height = map.getHeight();

    // Step 1: randomly fill map
    for (unsigned int y = 0; y < height; ++y)
    {
        for (unsigned int x = 0; x < width; ++x)
        {
            if (x == 0 || y == 0 || x == width - 1 || y == height - 1)
                map.setTile(x, y, 1);  // edges stay walls
            else
                map.setTile(x, y, (std::rand() % 100 < fillProbability) ? 1 : 0);
        }
    }

    // Step 2: iterate smoothing process
    for (int i = 0; i < iterations; ++i)
    {
        Map newMap(width, height);

        for (unsigned int y = 0; y < height; ++y)
        {
            for (unsigned int x = 0; x < width; ++x)
            {
                int wallCount = 0;

                // Count surrounding walls in 8 neighbors
                for (int dy = -1; dy <= 1; ++dy)
                {
                    for (int dx = -1; dx <= 1; ++dx)
                    {
                        if (dx == 0 && dy == 0) continue;
                        unsigned int nx = x + dx;
                        unsigned int ny = y + dy;

                        if (nx >= width || ny >= height || map.getTile(nx, ny) == 1)
                            wallCount++;
                    }
                }

                // Apply rules
                if (map.getTile(x, y) == 1)
                {
                    newMap.setTile(x, y, (wallCount >= 4) ? 1 : 0);
                }
                else
                {
                    newMap.setTile(x, y, (wallCount >= 5) ? 1 : 0);
                }
            }
        }

        map = newMap;  // swap maps
    }

    floodFillRegions(map);
}

void Generator::floodFillRegions(Map& map)
{
    unsigned int width = map.getWidth();
    unsigned int height = map.getHeight();

    Map regionMap(width, height);
    int regionId = 2;  // start at 2 because 0=floor, 1=wall
    std::map<int, std::vector<sf::Vector2i>> regions;

    for (unsigned int y = 0; y < height; ++y)
    {
        for (unsigned int x = 0; x < width; ++x)
        {
            if (map.getTile(x, y) != 0 || regionMap.getTile(x, y) != 0)
                continue;

            std::queue<sf::Vector2i> toCheck;
            toCheck.push({ (int)x, (int)y });
            regionMap.setTile(x, y, regionId);

            regions[regionId] = { { (int)x, (int)y } };

            while (!toCheck.empty())
            {
                sf::Vector2i p = toCheck.front();
                toCheck.pop();

                static const int dirX[] = { -1, 1, 0, 0 };
                static const int dirY[] = { 0, 0, -1, 1 };

                for (int i = 0; i < 4; ++i)
                {
                    int nx = p.x + dirX[i];
                    int ny = p.y + dirY[i];

                    if (nx < 0 || ny < 0 || nx >= (int)width || ny >= (int)height)
                        continue;

                    if (map.getTile(nx, ny) == 0 && regionMap.getTile(nx, ny) == 0)
                    {
                        regionMap.setTile(nx, ny, regionId);
                        toCheck.push({ nx, ny });
                        regions[regionId].push_back({ nx, ny });
                    }
                }
            }
            regionId++;
        }
    }

    // Find largest region
    int largestRegionId = -1;
    size_t largestSize = 0;

    for (const auto& [id, tiles] : regions)
    {
        if (tiles.size() > largestSize)
        {
            largestSize = tiles.size();
            largestRegionId = id;
        }
    }

    // Remove all other regions
    for (const auto& [id, tiles] : regions)
    {
        if (id == largestRegionId)
            continue;

        for (const sf::Vector2i& p : tiles)
            map.setTile(p.x, p.y, 1); // fill with wall
    }

    // Optional: connect other regions to main region (if desired)
    for (const auto& [id, tiles] : regions)
    {
        if (id == largestRegionId)
            continue;

        sf::Vector2i from = tiles[0]; // pick a random tile in the isolated region
        sf::Vector2i to = regions[largestRegionId][std::rand() % regions[largestRegionId].size()];
        connectPoints(map, from, to);
    }
}

void Generator::connectPoints(Map& map, const sf::Vector2i& a, const sf::Vector2i& b)
{
    sf::Vector2i current = a;

    while (current.x != b.x)
    {
        map.setTile(current.x, current.y, 0);
        current.x += (b.x > current.x) ? 1 : -1;
    }

    while (current.y != b.y)
    {
        map.setTile(current.x, current.y, 0);
        current.y += (b.y > current.y) ? 1 : -1;
    }
}



void Generator::WaveFunctionCollapse(Map& map)
{
    int width = map.getWidth();
    int height = map.getHeight();
    std::vector<std::vector<std::vector<int>>> wave(width, std::vector<std::vector<int>>(height));

    // Initialize wave with all possible pattern IDs
    for (int y = 0; y < height; ++y)
        for (int x = 0; x < width; ++x)
            for (const auto& pattern : patterns)
                wave[x][y].push_back(pattern.id);

    // Collapse cells progressively
    while (true)
    {
        int idx = getLowestEntropyCell(wave, width, height);
        if (idx == -1) break; // All cells collapsed

        int x = idx % width;
        int y = idx / width;

        collapseCell(wave, x, y);
        propagate(wave, width, height);
    }

    // Apply to Map
    for (int y = 0; y < height; ++y)
        for (int x = 0; x < width; ++x)
        {
            int patternId = wave[x][y][0];
            int tileValue = patterns[patternId].tiles[1][1]; // use center value
            map.setTile(x, y, tileValue);
        }
}

void Generator::propagate(std::vector<std::vector<std::vector<int>>>& wave, int width, int height)
{
    bool changed;
    do
    {
        changed = false;
        for (int y = 0; y < height; ++y)
        {
            for (int x = 0; x < width; ++x)
            {
                if (wave[x][y].size() == 1) continue;

                std::vector<int> possible = wave[x][y];
                std::vector<int> newPossible;

                for (int id : possible)
                {
                    bool compatible = true;
                    static const int dx[4] = { 0, 0, -1, 1 };
                    static const int dy[4] = { -1, 1, 0, 0 };

                    for (int dir = 0; dir < 4; ++dir)
                    {
                        int nx = x + dx[dir];
                        int ny = y + dy[dir];
                        if (nx < 0 || ny < 0 || nx >= width || ny >= height) continue;

                        bool neighborCompatible = false;
                        for (int nid : wave[nx][ny])
                            if (std::find(patterns[id].allowedNeighbors[dir].begin(), patterns[id].allowedNeighbors[dir].end(), nid) != patterns[id].allowedNeighbors[dir].end())
                                neighborCompatible = true;

                        if (!neighborCompatible)
                        {
                            compatible = false;
                            break;
                        }
                    }

                    if (compatible)
                        newPossible.push_back(id);
                }

                if (newPossible.size() != possible.size())
                {
                    wave[x][y] = newPossible;
                    changed = true;
                }
            }
        }
    } while (changed);
}

int Generator::getLowestEntropyCell(const std::vector<std::vector<std::vector<int>>>& wave, int width, int height)
{
    int minEntropy = INT_MAX;
    int idx = -1;

    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            int entropy = wave[x][y].size();
            if (entropy > 1 && entropy < minEntropy)
            {
                minEntropy = entropy;
                idx = y * width + x;
            }
        }
    }
    return idx;
}

void Generator::collapseCell(std::vector<std::vector<std::vector<int>>>& wave, int x, int y)
{
    int rndIdx = std::rand() % wave[x][y].size();
    int selected = wave[x][y][rndIdx];
    wave[x][y] = { selected };
}

void Generator::loadPatterns()
{
    patterns.clear();

    patterns.push_back({ 0, {
        {1,1,1},
        {1,0,1},
        {1,1,1}
    }, {{0,1,2,3,4,5},{0,1,2,3,4,5},{0,1,2,3,4,5},{0,1,2,3,4,5}} });

    patterns.push_back({ 1, {
        {1,1,1},
        {0,0,0},
        {1,1,1}
    }, {{0,1},{0,1},{0,1},{0,1}} });

    patterns.push_back({ 2, {
        {1,0,1},
        {0,0,0},
        {1,0,1}
    }, {{1,2},{1,2},{1,2},{1,2}} });

    patterns.push_back({ 3, {
        {1,1,1},
        {1,1,1},
        {1,1,1}
    }, {{3},{3},{3},{3}} });

    // Add more patterns with compatible allowedNeighbors
}