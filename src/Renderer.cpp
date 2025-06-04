#include "Renderer.hpp"

Renderer::Renderer(SDL_Renderer* renderer)
    : m_Renderer(renderer)
{}

void Renderer::RenderMap(const DungeonMap& map)
{
    for (int y = 0; y < map.GetHeight(); ++y)
    {
        for (int x = 0; x < map.GetWidth(); ++x)
        {
            SDL_FRect rect = { (float)x * m_TileSize, (float)y * m_TileSize, (float)m_TileSize, (float)m_TileSize };
            TileType tile = map.GetTile(x, y);
            switch (tile)
            {
                case TileType::Empty:
                    SDL_SetRenderDrawColor(m_Renderer, 20, 20, 20, 255);
                    break;
                case TileType::Floor:
                    SDL_SetRenderDrawColor(m_Renderer, 200, 200, 200, 255);
                    break;
                case TileType::Wall:
                    SDL_SetRenderDrawColor(m_Renderer, 100, 100, 100, 255);
                    break;
            }
            SDL_RenderFillRect(m_Renderer, &rect);
        }
    }
}