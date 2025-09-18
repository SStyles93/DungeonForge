#pragma once
#include "Map.hpp"
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <cmath>
#include <cstdlib>  // for std::rand
#include <ctime>
#include <map>
#include <random>
#include <queue>
#include <vector>
#include <unordered_set>
#include <chrono>

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

    // BSP

    void setMaxRoomEdgeSize(int size);

    // Automata related functions

    void setFillProbability(int value);
    void setIterations(int value);
    
    // Drunkard's Walk

    void setFillPercentage(float value);

private:


    Map m_map;
    AlgorithmType m_algorithmType = AlgorithmType::BinarySpacePartitioning;
    int m_seed = 0;
    std::mt19937 m_randomGenerator;
    int m_maxBorderSize = 15;
    int m_fillProbability = 45; //Automata - Value that defines the chances for the algo. to fill a tile or not
    int m_iterations = 5; //Automata - Number of iterations for the smoothing process
    float m_fillPercentage = 0.8f;


    void generateSeed();

    // Algorithms

    void generatePerlin(Map& map);
    void generateDrunkardsWalk(Map& map);
    void generateBSP(Map& map);
    void generateCellularAutomata(Map& map, int fillProbability, int iterations);
    void generateWFC(Map& map);

    //BSP

    /*Represents a rectangle defined by its position and size.*/
    /*x position / y position / width / height*/ 
    struct Rect
    {
        int x, y, width, height;
    public:
        std::pair<int, int> getCenter()
        {
            return { x + ((width / 2) + (width % 2)), y + ((height / 2) + (height % 2)) };
        }
    };

    void splitSpaces(std::vector<Rect>& spaces, int maxBorderSize);
    void createRoom(Map& map, const Rect& room);
    void connectRooms(Map&, std::vector<Rect>& spaces);

    /*/// <summary>
    /// Splits the given spaces into smaller regions based on the maximum leaf size.
    /// </summary>
    /// <param name="spaces: ">A reference to a vector of Rect objects representing the spaces to be split. The vector may be modified in place.</param>
    /// <param name="maxLeafSize: ">The maximum allowed size for each leaf region after splitting.</param>
    void splitSpace(std::vector<Rect>& spaces, int maxLeafSize);
    void connectRooms(Map& map, const std::pair<int,int>& pointA, const std::pair<int, int>& pointB);*/

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