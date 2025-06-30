#pragma once
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
