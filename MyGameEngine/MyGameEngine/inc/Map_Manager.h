//-----------------------------------------------------------------------------
// Author: Tom Solarino
// Description: This loades in Tiled maps 
//-----------------------------------------------------------------------------

#ifndef MAP_LOADER
#define MAP_LOADER
#include <vector>

class Map;
class Sprite_Batch;

class Map_Manager
{
public:
	Map_Manager();
	~Map_Manager();
	
	void Update(float a_dt);
	void Draw(Sprite_Batch *a_SB);

	void LoadNewMap(char *m_mapDataFile);

private:
	std::vector<Map> m_maps;
};
#endif