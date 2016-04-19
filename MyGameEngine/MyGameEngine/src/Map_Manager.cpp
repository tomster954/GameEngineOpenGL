#include "Map_Manager.h"
#include "Map.h"

Map_Manager::Map_Manager()
{

}

Map_Manager::~Map_Manager()
{

}

void Map_Manager::Update(float a_dt)
{

}

void Map_Manager::Draw(Sprite_Batch *a_SB)
{

}

void Map_Manager::LoadNewMap(char *a_mapDataFile)
{
	Map newMap = Map(a_mapDataFile);
	m_maps.push_back(newMap);
}