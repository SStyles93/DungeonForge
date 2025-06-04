#pragma once
#include "Map.hpp"
#include <SDL3/SDL.h>

class Renderer
{
public:
    Renderer(SDL_Renderer* renderer);
    void RenderMap(const Map& map);
private:
    SDL_Renderer* mRenderer;
};