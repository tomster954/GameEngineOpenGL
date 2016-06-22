//-----------------------------------------------------------------------------
// Author: Tom Solarino
// Description: This loades in Tiled maps 
//-----------------------------------------------------------------------------

#ifndef MAP_LOADER
#define MAP_LOADER
#include <vector>

class Map;
class Sprite_Batch;
class Application;
enum EMAPS
{
	MAP1,
	MAP2,
	MAP3
};

class Map_Manager
{
public:
	Map_Manager(Application *a_app);
	~Map_Manager();
	
	void Update(float a_dt);
	void Draw(Sprite_Batch *a_SB);

	void LoadNewMap(char *m_mapDataFile);

	void SetMap(EMAPS a_mapID){ m_mapID = a_mapID; };

private:
	Application *m_app;
	std::vector<Map*> m_maps;
	EMAPS m_mapID;
};
#endif