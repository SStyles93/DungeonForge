#pragma once
#include <iostream>
#include <string>
#include "DungeonMap.hpp"

class DungeonGenerator
{
public:
	DungeonGenerator();
	~DungeonGenerator();

	void Generate(DungeonMap map);

private:
	DungeonMap* m_DungeonMap = nullptr;
};
