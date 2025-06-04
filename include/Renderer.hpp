#pragma once
#include "Map.hpp"
#include <SFML/Graphics.hpp>

class Renderer
{
public:
    void render(sf::RenderWindow& window, const Map& map);
};
