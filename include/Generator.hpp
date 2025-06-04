#pragma once
#include "Map.hpp"
#include <vector>
#include <SFML/Graphics.hpp>

class Generator
{
public:
    void Perlin(Map& map);
    void DrunkardsWalk(Map& map);
    void BSP(Map& map);

private:
    struct Rect
    {
        int x, y, width, height;
    };

    void splitSpace(std::vector<Rect>& spaces, int maxLeafSize);
    void createRoom(Map& map, const Rect& room);
    void connectRooms(Map& map, const sf::Vector2i& pointA, const sf::Vector2i& pointB);
};
