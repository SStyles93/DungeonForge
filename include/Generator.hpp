#pragma once
#include "dllexport.h"
#include "Map.hpp"
//#include <SFML/Graphics.hpp>
#include <algorithm>
#include <cmath>
#include <cstdlib>  // for std::rand
#include <ctime>
#include <map>
#include <queue>
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

private:
    struct Rect
    {
        int x, y, width, height;
    };


    Map m_map;
    AlgorithmType m_algorithmType = AlgorithmType::Perlin;

    // Algorithms

    void generatePerlin(Map& map);
    void generateDrunkardsWalk(Map& map);
    void generateBSP(Map& map);
    void generateCellularAutomata(Map& map, int fillProbability, int iterations);
    void generateWFC(Map& map);

    //BSP

    void splitSpace(std::vector<Rect>& spaces, int maxLeafSize);
    void createRoom(Map& map, const Rect& room);
    void connectRooms(Map& map, const std::pair<int,int>& pointA, const std::pair<int, int>& pointB);

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

    PXP_DF_API int GetAlgorithm(Generator* instance, int type);
}