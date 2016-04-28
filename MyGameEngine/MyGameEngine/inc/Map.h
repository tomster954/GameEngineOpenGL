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
	std::string FindData(std::string a_word); //find the word and returns the following characters

	unsigned int m_tileWidth, m_tileHeight; //In pixels
	unsigned int m_mapWidth, m_mapHeight; //Number of tiles wide/high (Not Pixles)

	unsigned int m_tileSpacing, m_tileMargin; //In Pixels

	std::vector<char> m_fileData; //Entire file of map data
	std::vector<int> m_mapTileData; //just the tile data from m_fileData;
};
#endif