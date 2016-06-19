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

struct TileSet
{
	std::string tileSetName;
	Texture *m_texture;	//The entire tile sheet
	unsigned int tileWidth, tileHeight;		//In pixels
	unsigned int tileSpacing, tileMargin;	//In Pixels
	unsigned int columns, tileCount, rows;	//amount of columns in the tile sheet and the total amount of tiles
};

struct MapData
{
	std::string entireFile;					//Entire file of map data

	std::string tag_Map;					//Th tag "<map>" in the mapta file
	std::string tag_tileset;				//The tag "<tileset>" in the map data file
	std::string tag_image;					//The tag "<image>" in the map data file

	std::string orientation;				//orthogonal e.t.c.
	int mapWidth; 
	int mapHeight;							//Number of tiles wide/high (Not Pixles)	
	int tileWidth;
	int tileHeight;							//In pixels NOT THE SIZE ON TEXTURE SHEET

	std::string tileData;					//A string of all the tile IDs
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
	std::string FindDataBetween(std::string a_start, std::string a_end, std::string *a_file, bool a_includeSearchedWords);	//find the word and returns the following characters

	glm::vec2 FindTileTopLeft(int a_tileID);	//Uses the tile id to find the top left of that tile on the tile sheet

	MapData m_map_Data;

	TileSet m_tileSet;
	
	std::vector<std::vector<Tile*>> m_mapTiles;	//All the tiles for this map
};
#endif
