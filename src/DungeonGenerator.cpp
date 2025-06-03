#include "DungeonGenerator.hpp"

DungeonGenerator::DungeonGenerator(){}

DungeonGenerator::~DungeonGenerator(){}

void DungeonGenerator::Generate(DungeonMap map)
{
	*m_DungeonMap = map;
}