//-----------------------------------------------------------------------------
//Author:: Tom Solarino	
//Description:: This is a map for the game
//-----------------------------------------------------------------------------

#ifndef MAP
#define MAP
#include "glm/glm.hpp"

#include <vector>
class Application;
class Sprite_Batch;
class Texture;
class Tile;

//Contains all the data for the tile set/sheet
struct TileSet
{
	std::string tileSetName;
	Texture *m_texture;	//The entire tile sheet
	unsigned int tileWidth, tileHeight;		//In pixels
	unsigned int tileSpacing, tileMargin;	//In Pixels
	unsigned int columns, tileCount, rows;	//amount of columns in the tile sheet and the total amount of tiles
};

struct Object
{
	std::string name;	//The ojects name
	int objID;			//The objects ID
	glm::vec2 position;	//The objects Position (Top Left)
	glm::vec2 size;		//The width and height of this object
};

struct ObjectGroup
{
	std::string tag_objectGroup;	//Just the object group data from the entire map data
	std::string groupName;			//The name of the object group e.g "spawns"
	std::vector<Object*> objects;	//The objects in the object group
};

//Contains all the data for the map read from file
struct MapData
{
	std::string entireFile;		//Entire file of map data
								
	std::string tag_Map;		//Th tag "<map>" in the mapta file
	std::string tag_tileset;	//The tag "<tileset>" in the map data file
	std::string tag_image;		//The tag "<image>" in the map data file
	std::string orientation;	//orthogonal e.t.c.
								
	int mapWidth, mapHeight;	//Number of tiles wide/high (Not Pixles)	
	int tileWidth, tileHeight;	//The size of a map tile
								
	std::string tileData;		//A string of all the tile IDs

	ObjectGroup objectGroup;	//All the object groups for this map
};

class Map
{
public:
	Map(char *a_mapDataFile, Application *a_app);
	~Map();

	void Load();

	//Update
	void Update(float a_dt);

	//Draws this specific map
	void Draw(Sprite_Batch *a_pSB);

private:
	//private functions
	void LoadTiles();							//Creates and adds all the tile to the 2d vector
	void LoadMapData(char *a_mapDataFile);		//Reads in the map file 
	void SortMapData();							//Reads vars from map file like tile width e.t.c
	void SortObjectGroups();					//finds and sorts object groupd from the map file data
	void SortTileSets();						//find and sort tile set data from the map file
	void FindVisibleTiles();					//Finds the tiles on the screen
	
	std::string FindDataBetween(std::string a_start, std::string a_end, std::string *a_file, bool a_includeSearchedWords, int a_occurance);	//Returns the string between the "start" and "end" words on whichever occurance
	int WordCount(std::string a_word, std::string *a_file);		//Finds the nuber of time a specific word appears
	glm::vec2 FindTileTopLeft(int a_tileID);					//Uses the tile id to find the top left of that tile on the tile sheet

	//private vars
	Application *m_app;		//a pointer to the application
	MapData m_map_Data;		//contains all data from the map file
	TileSet m_tileSet;		//contains the tile sets data

	std::vector<std::vector<Tile*>> m_mapTiles;			//All the tiles for this map
	std::vector<Tile*> m_visibleMapTiles;				//All the visible tiles on this map
};
#endif
