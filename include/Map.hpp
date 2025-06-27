#pragma once
#include "dllexport.h"
#include <vector>

class Map
{
public:
	Map(unsigned int width, unsigned int height);

	void setTile(unsigned int x, unsigned int y, int value);
	int getTile(unsigned int x, unsigned int y) const;
	unsigned int getWidth() const;
	unsigned int getHeight() const;

private:
	unsigned int width;
	unsigned int height;
	std::vector<int> tiles;
};


//extern "C"
//{
//	PXP_DF_API Map* CreateMap(unsigned int width, unsigned int height);
//
//	PXP_DF_API void DeleteMap(Map* instance);
//
//
//	PXP_DF_API void SetTile(Map* instance, unsigned int x, unsigned int y, int value);
//
//	//PXP_DF_API int GetTile(Map* instance, unsigned int x, unsigned int y);
//
//	
//	PXP_DF_API int GetWidth(Map* instance);
//
//	PXP_DF_API int GetHeight(Map* instance);
//}