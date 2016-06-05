//-----------------------------------------------------------------------------
// Author: Tom Solarino
// Description: This loades in Tiled maps 
//-----------------------------------------------------------------------------

#ifndef MAP_LOADER
#define MAP_LOADER
#include <vector>

class Map;
class Sprite_Batch;

enum EMAPS
{
	MAP1,
	MAP2,
	MAP3
};

class Map_Manager
{
public:
	Map_Manager();
	~Map_Manager();
	
	void Update(float a_dt);
	void Draw(Sprite_Batch *a_SB, EMAPS a_mapID);

	void LoadNewMap(char *m_mapDataFile);

private:
	std::vector<Map> m_maps;
};
#endif