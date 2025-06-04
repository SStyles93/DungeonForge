#include "Renderer.hpp"

#define TILE_SIZE 16

//Renderer::Renderer(SDL_Renderer* renderer)
//	: mRenderer(renderer)
//{}

//void Renderer::RenderMap(const Map& map)
//{
	//int width = map.GetWidth();
	//int height = map.GetHeight();

	//SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);

	//for (int y = 0; y < height; ++y)
	//{
	//	for (int x = 0; x < width; ++x)
	//	{

	//		SDL_FRect rect;
	//		rect.x = x * TILE_SIZE;
	//		rect.y = y * TILE_SIZE;
	//		rect.w = TILE_SIZE;
	//		rect.h = TILE_SIZE;

	//		SDL_RenderFillRect(mRenderer, &rect);

	//	}
	//}
//}