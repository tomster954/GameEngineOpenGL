#include "Map_Manager.h"
#include "Map.h"

#include <vector>

Map_Manager::Map_Manager()
{

}

Map_Manager::~Map_Manager()
{
	for (int i = 0; i < m_maps.size(); i++)
		delete m_maps[i];
}

void Map_Manager::Update(float a_dt)
{

}

void Map_Manager::Draw(Sprite_Batch *a_SB, EMAPS a_mapID)
{
	m_maps[a_mapID]->Draw(a_SB);
}

void Map_Manager::LoadNewMap(char *a_mapDataFile)
{
	Map *newMap = new Map(a_mapDataFile);
	m_maps.push_back(newMap);
}