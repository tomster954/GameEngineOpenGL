//-----------------------------------------------------------------------------
//Author:: Tom Solarino	
//Description:: This is a map for the game
//-----------------------------------------------------------------------------

#ifndef MAP
#define MAP
#include "glm/glm.hpp"

#include <vector>
class Sprite_Batch;
class Texture;
class Tile;

struct TileSheet
{
	Texture *m_texture;	//The entire tile sheet

	unsigned int tileWidth, tileHeight;		//In pixels
	unsigned int tileSpacing, tileMargin;	//In Pixels
	unsigned int columns, tileCount, rows;	//amount of columns in the tile sheet and the total amount of tiles
};

class Map
{
public:
	Map(char *a_mapDataFile);
	~Map();

	void Load(char *a_mapDataFile);

	//Update
	void Update();

	//Draws this specific map
	void Draw(Sprite_Batch *a_pSB);

	//Loads all tiles for the map
	void LoadTiles();

private:
	void ReadMapData(char *a_mapDataFile);		//Reads in the map file 
	void SortMapData();							//Reads vars from map file like tile width e.g.
	glm::vec2 FindTileTopLeft(int a_tileID);	//Uses the tile id to find the top left of that tile on the tile sheet

	TileSheet m_tileSheet; 
	std::string FindData(std::string a_word, char a_endChar);	//find the word and returns the following characters

	unsigned int m_mapWidth, m_mapHeight;		//Number of tiles wide/high (Not Pixles)

	std::vector<char> m_fileData;				//Entire file of map data
	std::string m_rawTileData;					//A string of all the tile IDs
	std::vector<std::vector<Tile*>> m_mapTiles;//just the tile data from m_fileData
};
#endif
