#pragma once
#include "Map.hpp"
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <cmath>
#include <cstdlib>  // for std::rand
#include <ctime>
#include <map>
#include <queue>
#include <vector>

class Generator
{
public:
    void Perlin(Map& map);
    void DrunkardsWalk(Map& map);
    void BSP(Map& map);
    void CellularAutomata(Map& map, int fillProbability, int iterations);
    void WaveFunctionCollapse(Map& map);

private:
    struct Rect
    {
        int x, y, width, height;
    };

    //BSP
    void splitSpace(std::vector<Rect>& spaces, int maxLeafSize);
    void createRoom(Map& map, const Rect& room);
    void connectRooms(Map& map, const sf::Vector2i& pointA, const sf::Vector2i& pointB);

    //Cellular Automata
    void floodFillRegions(Map& map);
    void connectPoints(Map& map, const sf::Vector2i& a, const sf::Vector2i& b);

    
    //WaveFunctionCollapse
    struct Pattern
    {
        int id;
        std::vector<std::vector<int>> tiles; // 3x3 tile data: 0=floor, 1=wall

        // Allowed neighbor pattern IDs by direction: 0=up, 1=down, 2=left, 3=right
        std::vector<int> allowedNeighbors[4];
    };

    std::vector<Pattern> patterns;

    void loadPatterns();
    void propagate(std::vector<std::vector<std::vector<int>>>& wave, int width, int height);
    int getLowestEntropyCell(const std::vector<std::vector<std::vector<int>>>& wave, int width, int height);
    void collapseCell(std::vector<std::vector<std::vector<int>>>& wave, int x, int y);

};