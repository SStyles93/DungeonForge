#pragma once
#include "DungeonMap.hpp"
#include <SDL3/SDL.h>

class Renderer
{
public:
    Renderer(SDL_Renderer* renderer);
    void RenderMap(const DungeonMap& map);

private:
    SDL_Renderer* m_Renderer;
    int m_TileSize = 16;
};
