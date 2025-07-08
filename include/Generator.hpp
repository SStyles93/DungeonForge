#pragma once
#include "dllexport.h"
#include "Map.hpp"
#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstdlib>  // for std::rand
#include <ctime>
#include <list>
#include <map>
#include <queue>
#include <random>
#include <vector>

enum AlgorithmType
{
    BinarySpacePartitioning,
    CellularAutomata,
    DrunkardsWalk,
    Perlin,
    WaveFunctionCollapse
};

class Generator
{
public:
    Generator(unsigned int width, unsigned int height);

    void generate();

    
    Map& getMap();

    void setAlgorithm(AlgorithmType type);
    int getAlgorithm();
    void setMap(Map& map);
    void setSeed(int seed);

    // BSP related functions

    void setMaxRoomEdgeSize(int size);
    
    // Automata related functions

    void setFillProbability(int value);
    void setIterations(int value);

private:
    struct Rect
    {
        int x, y, width, height;
    public:
        std::pair<int, int> getCenter() 
        { 
            return { x + (width / 2 + width % 2), y + (height / 2 + height % 2) };
        }
    };


    Map m_map; //Map object used to generate maps
    AlgorithmType m_algorithmType = AlgorithmType::Perlin; //Algorithm Type selection
    std::mt19937 m_randomGenerator; //Mercene-twister engine (rdn)
    int m_seed = -1; //Generator - Seed used by the mercene twister engine (-1 random - INT32_MAX)
    int m_maxBorderSize = 10; //BSP - Value that defines when the algorithm will stop cutting rooms
    int m_fillProbability = 45; //Automata - Value that defines the chances for the algo. to fill a tile or not
    int m_iterations = 5; //Automata - Number of iterations for the smoothing process

    void generateSeed();

    //Generator Algorithms

    void generatePerlin(Map& map);
    void generateDrunkardsWalk(Map& map);
    void generateBSP(Map& map);
    void generateCellularAutomata(Map& map, int fillProbability, int iterations);
    void generateWFC(Map& map);

    //BSP

    void splitSpaces(std::vector<Rect>& spaces, int maxBorderSize);
    void createRoom(Map& map, const Rect& room);
    void connectRooms(Map& map, std::vector<Rect>& spaces);

    //Cellular Automata

    void floodFillRegions(Map& map);
    void connectPoints(Map& map, const std::pair<int, int>& pointA, const std::pair<int, int>& pointB);

    
    //WaveFunctionCollapse
    
    struct Pattern
    {
        int id;
        std::vector<std::vector<int>> tiles; // 3x3 tile data: 0=floor, 1=wall

        // Allowed neighbor pattern IDs by direction: 0=up, 1=down, 2=left, 3=right
        std::vector<int> allowedNeighbors[4];
    };
    std::vector<Pattern> m_patterns;

    void loadPatterns();
    void propagate(std::vector<std::vector<std::vector<int>>>& wave, int width, int height);
    int getLowestEntropyCell(const std::vector<std::vector<std::vector<int>>>& wave, int width, int height);
    void collapseCell(std::vector<std::vector<std::vector<int>>>& wave, int x, int y);

};

extern "C" 
{
    PXP_DF_API Generator* CreateGenerator(unsigned int width, unsigned int height);

    PXP_DF_API void DeleteGenerator(Generator* instance);

    PXP_DF_API void Generate(Generator* instance);

    PXP_DF_API Map& GetMap(Generator* instance);

    PXP_DF_API int GetTile(Generator* instance, unsigned int x, unsigned int y);

    PXP_DF_API void SetAlgorithm(Generator* instance, int type);

    PXP_DF_API void SetSeed(Generator* instance, int seed);

    PXP_DF_API void SetMaxRoomEdgeSize(Generator* instance, int size);

    PXP_DF_API void SetFillProbability(Generator* instance, int value);

    PXP_DF_API void SetIterations(Generator* instance, int value);
}