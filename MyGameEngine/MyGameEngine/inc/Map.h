//-----------------------------------------------------------------------------
//Author:: Tom Solarino	
//Description:: This is a map for the game
//-----------------------------------------------------------------------------

#ifndef MAP
#define MAP
#include <vector>

class Map
{
public:
	Map(char *a_mapDataFile);
	~Map();

private:
	void ReadMapData(char *a_mapDataFile);
	void SortMapData();
	std::string FindData(char *word);

	unsigned int m_tileWidth, m_tileHeight;
	unsigned int m_mapWidth, m_mapHeight;

	unsigned int m_tileSpacing, m_margin;

	std::vector<char> m_fileData;
	std::vector<int> m_mapTileData;
};
#endif