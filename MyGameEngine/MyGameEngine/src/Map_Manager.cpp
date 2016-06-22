#include "Map_Manager.h"
#include "Map.h"

#include "Application.h"

#include <vector>

Map_Manager::Map_Manager(Application *a_app)
{
	m_app = a_app;
}

Map_Manager::~Map_Manager()
{
	for (int i = 0; i < m_maps.size(); i++)
		delete m_maps[i];
}

void Map_Manager::Update(float a_dt)
{
	m_maps[m_mapID]->Update(a_dt);
}

void Map_Manager::Draw(Sprite_Batch *a_SB)
{
	m_maps[m_mapID]->Draw(a_SB);
}

void Map_Manager::LoadNewMap(char *a_mapDataFile)
{
	Map *newMap = new Map(a_mapDataFile, m_app);
	m_maps.push_back(newMap);
}