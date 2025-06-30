#include "Generator.hpp"

Generator::Generator(unsigned int width, unsigned int height) : m_map(Map(width, height))
{};

void Generator::generate()
{
    generateSeed();

    switch (m_algorithmType)
    {
        case BinarySpacePartitioning:
            generateBSP(m_map);
            break;
        case CellularAutomata:
            generateCellularAutomata(m_map, 45, 5);
            break;
        case DrunkardsWalk:
            generateDrunkardsWalk(m_map);
            break;
        case Perlin:
            generatePerlin(m_map);
            break;
        case WaveFunctionCollapse:
            //generateWFC(m_map);
            break;
        default:
            break;
    }
}

void Generator::setAlgorithm(AlgorithmType type)
{
    m_algorithmType = type;
}

int Generator::getAlgorithm()
{
    return m_algorithmType;
}

Map& Generator::getMap()
{
    return m_map;
}

void Generator::setMap(Map& map)
{
    m_map = map;
}

void Generator::setSeed(int seed)
{
    m_seed = seed;
}


void Generator::generateSeed()
{
    unsigned int currentSeed;
    if (m_seed == -1)
        currentSeed = std::chrono::system_clock::now().time_since_epoch().count();
    else
        currentSeed = m_seed;

    m_randomGenerator.seed(currentSeed);
}


void Generator::generatePerlin(Map& map)
{
    for (unsigned int y = 0; y < map.getHeight(); ++y)
    {
        for (unsigned int x = 0; x < map.getWidth(); ++x)
        {
            // Randomly assign 0 (floor) or 1 (wall)
            int tileValue = m_randomGenerator() % 2;
            map.setTile(x, y, tileValue);
        }
    }
}

//DLL EXPORT

PXP_DF_API Generator* CreateGenerator(unsigned int width, unsigned int height)
{
    return new Generator(width, height);
}

PXP_DF_API void DeleteGenerator(Generator* instance)
{
    delete instance;
}

PXP_DF_API void Generate(Generator* instance)
{
    if (instance == nullptr) return;
    instance->generate();
}

PXP_DF_API Map& GetMap(Generator* instance)
{
    if (instance != nullptr)
    return instance->getMap();
}

PXP_DF_API int GetTile(Generator* instance, unsigned int x, unsigned int y)
{
    return instance ? instance->getMap().getTile(x, y) : 0;
}

PXP_DF_API void SetAlgorithm(Generator* instance, int type)
{
    if (instance != nullptr)
    {
        instance->setAlgorithm((AlgorithmType)type);
    }
}

PXP_DF_API void SetSeed(Generator* instance, int seed)
{
    if (instance == nullptr) return;
    instance->setSeed(seed);
}




void Generator::generateDrunkardsWalk(Map& map)
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
        int dir = m_randomGenerator() % 4;

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



void Generator::generateBSP(Map& map)
{
    // Fill map with walls
    for (unsigned int y = 0; y < map.getHeight(); ++y)
        for (unsigned int x = 0; x < map.getWidth(); ++x)
            map.setTile(x, y, 1);

    std::vector<Rect> spaces;
    spaces.push_back({ 1, 1, (int)map.getWidth() - 2, (int)map.getHeight() - 2 });

    int maxLeafSize = 20;
    splitSpace(spaces, maxLeafSize);

    std::vector<std::pair<int, int>> roomCenters;

    for (const Rect& space : spaces)
    {
        // Room size
        int roomWidth = 4 + m_randomGenerator() % (space.width);
        int roomHeight = 4 + m_randomGenerator() % (space.height);

        int roomX = space.x + m_randomGenerator() % (space.width);
        int roomY = space.y + m_randomGenerator() % (space.height);

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
            bool splitH = m_randomGenerator() % 2;
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
                int split = 4 + m_randomGenerator() % (space.height - 8);
                newSpaces.push_back({ space.x, space.y, space.width, split });
                newSpaces.push_back({ space.x, space.y + split, space.width, space.height - split });
            }
            else
            {
                int split = 4 + m_randomGenerator() % (space.width - 8);
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

void Generator::connectRooms(Map& map, const std::pair<int, int>& pointA, const std::pair<int, int>& pointB)
{
    std::pair<int, int> current = pointA;

    while (current.first != pointB.first)
    {
        map.setTile(current.first, current.second, 0);
        current.first += (pointB.first > current.first) ? 1 : -1;
    }

    while (current.second != pointB.second)
    {
        map.setTile(current.first, current.second, 0);
        current.second += (pointB.second > current.second ? 1 : -1);
    }
}



void Generator::generateCellularAutomata(Map& map, int fillProbability, int iterations)
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
                map.setTile(x, y, (m_randomGenerator() % 100 < fillProbability) ? 1 : 0);
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
    std::map<int, std::vector<std::pair<int,int>>> regions;

    for (unsigned int y = 0; y < height; ++y)
    {
        for (unsigned int x = 0; x < width; ++x)
        {
            if (map.getTile(x, y) != 0 || regionMap.getTile(x, y) != 0)
                continue;

            std::queue<std::pair<int, int>> toCheck;
            toCheck.push({ (int)x, (int)y });
            regionMap.setTile(x, y, regionId);

            regions[regionId] = { { (int)x, (int)y } };

            while (!toCheck.empty())
            {
                std::pair<int, int> p = toCheck.front();
                toCheck.pop();

                static const int dirX[] = { -1, 1, 0, 0 };
                static const int dirY[] = { 0, 0, -1, 1 };

                for (int i = 0; i < 4; ++i)
                {
                    int nx = p.first + dirX[i];
                    int ny = p.second + dirY[i];

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

        for (const std::pair<int, int>& p : tiles)
            map.setTile(p.first, p.second, 1); // fill with wall
    }

    // Optional: connect other regions to main region (if desired)
    for (const auto& [id, tiles] : regions)
    {
        if (id == largestRegionId)
            continue;

        std::pair<int, int> from = tiles[m_randomGenerator() % tiles.size()];
        // pick a random tile in the isolated region
        std::pair<int, int> to = regions[largestRegionId][m_randomGenerator() % regions[largestRegionId].size()];
        connectPoints(map, from, to);
    }
}

void Generator::connectPoints(Map& map, const std::pair<int,int>& pointA, const std::pair<int, int>& pointB)
{
    std::pair<int, int> current = pointA;

    while (current.first != pointB.first)
    {
        map.setTile(current.first, current.second, 0);
        current.first += (pointB.first > current.first) ? 1 : -1;
    }

    while (current.second != pointB.second)
    {
        map.setTile(current.first, current.second, 0);
        current.second += (pointB.second > current.second) ? 1 : -1;
    }
}


#pragma region TODO

void Generator::generateWFC(Map& map)
{
    loadPatterns();

    int width = map.getWidth();
    int height = map.getHeight();
    std::vector<std::vector<std::vector<int>>> wave(width, std::vector<std::vector<int>>(height));

    // Initialize wave with all possible pattern IDs
    for (int y = 0; y < height; ++y)
        for (int x = 0; x < width; ++x)
            for (const auto& pattern : m_patterns)
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
            int tileValue = m_patterns[patternId].tiles[1][1]; // use center value
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
                            if (std::find(m_patterns[id].allowedNeighbors[dir].begin(), m_patterns[id].allowedNeighbors[dir].end(), nid) != m_patterns[id].allowedNeighbors[dir].end())
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
    int rndIdx = m_randomGenerator() % wave[x][y].size();
    int selected = wave[x][y][rndIdx];
    wave[x][y] = { selected };
}

void Generator::loadPatterns()
{
    m_patterns.clear();

    m_patterns.push_back({ 0, {
        {1,1,1},
        {1,1,1},
        {1,1,1}
    }, {{0,1,3,5,6,7,8},{0,1,3,5,6,7,8},{0,1,3,5,6,7,8},{0,1,3,5,6,7,8}} });

    // Open center
    m_patterns.push_back({ 1, {
        {1,1,1},
        {1,0,1},
        {1,1,1}
    }, {{1,2,4,6,7},{1,2,4,6,7},{1,2,4,6,7},{1,2,4,6,7}} });

    // Horizontal corridor
    m_patterns.push_back({ 2, {
        {1,1,1},
        {0,0,0},
        {1,1,1}
    }, {{1,2,4,6,7},{1,2,4,6,7},{2,4,5,7,8},{2,4,5,7,8}} });

    // Vertical corridor
    m_patterns.push_back({ 3, {
        {1,0,1},
        {1,0,1},
        {1,0,1}
    }, {{3,4,5,6,7,8},{3,4,5,6,7,8},{1,3,4,6,7},{1,3,4,6,7}} });

    // Top-left corner
    m_patterns.push_back({ 4, {
        {1,1,1},
        {1,0,0},
        {1,0,1}
    }, {{1,2,3,4,6},{1,2,3,4,6},{1,2,3,4,6},{1,2,3,4,6}} });

    // Top-right corner
    m_patterns.push_back({ 5, {
        {1,1,1},
        {0,0,1},
        {1,0,1}
    }, {{1,2,3,5,7},{1,2,3,5,7},{1,2,3,5,7},{1,2,3,5,7}} });

    // Bottom-left corner
    m_patterns.push_back({ 6, {
        {1,0,1},
        {1,0,0},
        {1,1,1}
    }, {{1,2,3,6,8},{1,2,3,6,8},{1,2,3,6,8},{1,2,3,6,8}} });

    // Bottom-right corner
    m_patterns.push_back({ 7, {
        {1,0,1},
        {0,0,1},
        {1,1,1}
    }, {{1,2,3,7,8},{1,2,3,7,8},{1,2,3,7,8},{1,2,3,7,8}} });

    // T-intersection
    m_patterns.push_back({ 8, {
        {1,0,1},
        {0,0,0},
        {1,1,1}
    }, {{1,2,3,8},{1,2,3,8},{1,2,3,8},{1,2,3,8}} });
    // Add more patterns with compatible allowedNeighbors
}

#pragma endregion
