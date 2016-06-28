#include "Map.h"

#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>

#include "Sprite_Batch.h"
#include "Tile.h"
#include "Application.h"
#include "Camera.h"

Map::Map(char *a_mapDataFile, Application*a_app)
{
	m_app = a_app;
	LoadMapData(a_mapDataFile);

	if (m_map_Data.entireFile != "ERROR READING FILE")
		Load();
}

Map::~Map()
{
	delete m_tileSet.m_texture;
}

void Map::Load()
{
	//resizing vectors
	m_visibleMapTiles.resize(20, new Tile());

	//sorts the loaded map file into vars
	SortMapData();
	SortObjectGroups();
	SortTileSets();

	//resizing vectors
	m_mapTiles.resize(m_map_Data.mapHeight, std::vector<Tile*>(m_map_Data.mapWidth, new Tile()));

	//creates and loads all the tiles on this map
	LoadTiles();

}

void Map::Update(float a_dt)
{
	FindVisibleTiles();
}

void Map::Draw(Sprite_Batch *a_SB)
{
	for (int i = 0; i < m_visibleMapTiles.size(); i++)
	{
		m_visibleMapTiles[i]->Draw(a_SB);
	}
}

void Map::LoadMapData(char *a_mapDataFile)
{
	std::ifstream ifs(a_mapDataFile);
	m_map_Data.entireFile = "ERROR READING FILE";

	if (ifs)
	{
		//get the length of the file
		ifs.seekg(0, std::ios::end);
		std::streampos length = ifs.tellg();
		ifs.seekg(0, std::ios::beg);

		//create a buffer to contain the file contents
		std::vector<char> buffer(length);
		ifs.read(&buffer[0], length);

		std::string s(buffer.begin(), buffer.end());
		m_map_Data.entireFile = FindDataBetween("<map ", "</map>", &s, true, 1);
	}
}

void Map::SortMapData()
{
	//loading map data
	m_map_Data.tag_Map		= FindDataBetween("<map ", ">", &m_map_Data.entireFile, true, 1);
	m_map_Data.tag_tileset	= FindDataBetween("<tileset ", "</tileset>", &m_map_Data.entireFile, true, 1);
	m_map_Data.tag_image	= FindDataBetween("<image ", "/>", &m_map_Data.tag_tileset, true, 1);
	
	m_map_Data.orientation	= FindDataBetween("orientation=\"", "\"", &m_map_Data.tag_Map, false, 1);
	
	m_map_Data.mapWidth		= std::stoi(FindDataBetween("width=\"", "\"", &m_map_Data.tag_Map, false, 1));
	m_map_Data.mapHeight	= std::stoi(FindDataBetween("height=\"", "\"", &m_map_Data.tag_Map, false, 1));
	m_map_Data.tileWidth	= std::stoi(FindDataBetween("tilewidth=\"", "\"", &m_map_Data.tag_Map, false, 1));
	m_map_Data.tileHeight	= std::stoi(FindDataBetween("tileheight=\"", "\"", &m_map_Data.tag_Map, false, 1));

	m_map_Data.tileData = FindDataBetween("<data encoding=\"csv\">\n", "<", &m_map_Data.entireFile, false, 1);
}

void Map::SortObjectGroups()
{	
	//getting the object group data
	m_map_Data.objectGroup.tag_objectGroup = FindDataBetween("<objectgroup ", "</objectgroup>", &m_map_Data.entireFile, true, 1);
	m_map_Data.objectGroup.groupName = FindDataBetween("<objectgroup name=\"", "\"", &m_map_Data.objectGroup.tag_objectGroup, false, 1);

	m_map_Data.objectGroup.objects.resize(WordCount("<object ", &m_map_Data.objectGroup.tag_objectGroup));
	for (int i = 0; i < m_map_Data.objectGroup.objects.size(); i++)
	{
		m_map_Data.objectGroup.objects[i] = new Object();
		m_map_Data.objectGroup.objects[i]->name = FindDataBetween("\" name=\"", "\"", &m_map_Data.objectGroup.tag_objectGroup, false, i + 1);

		m_map_Data.objectGroup.objects[i]->objID		= std::stoi(FindDataBetween("id=\"", "\"", &m_map_Data.objectGroup.tag_objectGroup, false, i + 1));
		m_map_Data.objectGroup.objects[i]->position.x	= (float)std::stoi(FindDataBetween("x=\"", "\"", &m_map_Data.objectGroup.tag_objectGroup, false, i + 1));
		m_map_Data.objectGroup.objects[i]->position.y	= (float)std::stoi(FindDataBetween("y=\"", ">", &m_map_Data.objectGroup.tag_objectGroup, false, i + 1));
		m_map_Data.objectGroup.objects[i]->size.x		= (float)std::stoi(FindDataBetween("width=\"", "\"", &m_map_Data.objectGroup.tag_objectGroup, false, i + 1));
		m_map_Data.objectGroup.objects[i]->size.y		= (float)std::stoi(FindDataBetween("height=\"", ">", &m_map_Data.objectGroup.tag_objectGroup, false, i + 1));
	}
}

void Map::SortTileSets()
{
	//loading just tile set data
	m_tileSet.tileSetName = FindDataBetween("name=\"", "\"", &m_map_Data.tag_tileset, false, 1);

	m_tileSet.tileWidth = std::atoi(FindDataBetween("tilewidth=\"", "\"", &m_map_Data.tag_tileset, false, 1).c_str());
	m_tileSet.tileHeight = std::atoi(FindDataBetween("tileheight=\"", "\"", &m_map_Data.tag_tileset, false, 1).c_str());
	m_tileSet.tileSpacing = std::atoi(FindDataBetween("spacing=\"", "\"", &m_map_Data.tag_tileset, false, 1).c_str());
	m_tileSet.tileMargin = std::atoi(FindDataBetween("margin=\"", "\"", &m_map_Data.tag_tileset, false, 1).c_str());
	m_tileSet.columns = std::atoi(FindDataBetween("columns=\"", "\"", &m_map_Data.tag_tileset, false, 1).c_str());
	m_tileSet.tileCount = std::atoi(FindDataBetween("tilecount=\"", "\"", &m_map_Data.tag_tileset, false, 1).c_str());

	//calculating rows in the tile sheet off read data
	m_tileSet.rows = m_tileSet.tileCount / m_tileSet.columns;

	//load the tile map assosiated with this map
	std::string filelocation = "./resources/Maps/";
	filelocation.append(FindDataBetween("image source=\"", "\"", &m_map_Data.tag_image, false, 1));

	//setting the tile sets texture sheet
	m_tileSet.m_texture = new Texture(_strdup(filelocation.c_str()), glm::vec2(0), glm::vec2(0), glm::vec3(0, 0, -500), glm::vec2(0, 0));
}

void Map::LoadTiles()
{
	//setting up vars
	int tileCount = m_map_Data.mapWidth * m_map_Data.mapHeight;
	int row = 0;
	int col = 0;
	int initialVal = 0;

	//Filling the 2d vector of tiles
	for (int i = 0; i < m_map_Data.tileData.size(); i++)
	{
		//if we reach a new line
		if (m_map_Data.tileData[i] == '\n')
		{
			row++;
			col = 0;
			continue;
		}

		if (m_map_Data.tileData[i] == ',')
		{
			col++;
			continue;
		}

		//finds how many digits are in the current ID
		int digits = 0;
		int tileID = 1;
		for (int j = i; j < m_map_Data.tileData.size(); j++)
		{
			digits++;
			if (m_map_Data.tileData[j + 1] == ',' || m_map_Data.tileData[j + 1] == '\n')
			{
				//Takes the tiles id from the string and coverts it into an int
				tileID = std::stoi(m_map_Data.tileData.substr(i, digits));
				i = j;
				break;
			}
		}

		//setting up the next tiles vars
		glm::vec2 quadSize = glm::vec2(m_map_Data.tileWidth, m_map_Data.tileHeight);
		glm::vec2 portionSize = glm::vec2(m_tileSet.tileWidth, m_tileSet.tileHeight);
		glm::vec2 topLeftPx = FindTileTopLeft(tileID);

		//moves the camera to the middle of the map
		float x, y;
		x = m_map_Data.mapWidth * portionSize.x / 2;
		y = m_map_Data.mapHeight * portionSize.y / 2;
		m_app->GetCamera()->SetPosition(glm::vec3(x, -y, m_app->GetCamera()->GetPosition().z));

		//Tiles position
		glm::vec3 worldPos = glm::vec3(quadSize.x * col, -quadSize.y * row - quadSize.y, 0);

		//creat a new tile and add it to the other tiles
		Tile *tile = new Tile();
		tile->Initialise(m_tileSet.m_texture, tileID, quadSize, portionSize, worldPos, topLeftPx);
		m_mapTiles[row][col] = tile;
	}
}

std::string Map::FindDataBetween(std::string a_start, std::string a_end, std::string *a_file, bool a_includeSearchedWords, int a_occurance)
{
	std::size_t startPos = 0;
	std::size_t endPos = 0;
	std::string result("");

	startPos = a_file->find(a_start, startPos);

	for (int i = 1; i < a_occurance; i++)
		startPos = a_file->find(a_start, startPos + a_start.length());

	endPos = a_file->find(a_end, startPos + a_start.length());

	if (startPos == std::string::npos || endPos == std::string::npos)
		return "word not found";

	//checks whether to include searched words
	if (!a_includeSearchedWords)
		startPos += a_start.length();
	else
		endPos += a_end.length();

	int diff = endPos - startPos;
	result = a_file->substr(startPos, diff);
	
	return result;
}

int Map::WordCount(std::string a_word, std::string *a_file)
{
	int result = 0;
	std::size_t startPos = a_file->find(a_word);

	while (startPos != std::string::npos)
	{
		result++;
		startPos = a_file->find(a_word, startPos + 1);
	}

	return result;

}

glm::vec2 Map::FindTileTopLeft(int a_tileID)
{
	glm::vec2 pos = glm::vec2(0);

	//X
	//------------------------------------
	int col = a_tileID;

	//finding the column that this tile sits
	for (col; col > m_tileSet.columns;)
		col -= m_tileSet.columns;

	pos.x += m_tileSet.tileMargin;
	pos.x += ((col - 1) * m_tileSet.tileWidth) + ((col - 1) * m_tileSet.tileSpacing);
	pos.x += 0.5f; //because the texel coordinate is the middle of a pixel
	//------------------------------------

	//Y
	//------------------------------------
	int row;
	row = (a_tileID - 1) / m_tileSet.columns;
	
	pos.y += m_tileSet.tileMargin;
	pos.y += (row * m_tileSet.tileHeight) + (row * m_tileSet.tileSpacing);

	//------------------------------------

	return pos;
}

void Map::FindVisibleTiles()
{
	m_visibleMapTiles.clear();
	int centreTileRow, centreTileCol;
	centreTileRow = 0;
	centreTileCol = 0;

	//finding tile nearest camera/player
	centreTileCol = (int)m_app->GetCamera()->GetPosition().x / m_map_Data.tileWidth;
	centreTileRow = (int)-m_app->GetCamera()->GetPosition().y / m_map_Data.tileHeight;

	int searchsize = 18;

	for (int row = centreTileRow - searchsize; row < centreTileRow + searchsize; row++)
	{
		//break if we have no rows left
		if (row >= m_map_Data.mapHeight)
			break;
		//if the row is below 0 just continue
		if (row < 0 )
			continue;

		for (int col = centreTileCol - searchsize; col < centreTileCol + searchsize; col++)
		{
			//break if we have no cols left
			if (col >= m_map_Data.mapWidth)
				break;
			//Check col is valid
			if (col < 0)
				continue;
			
			m_visibleMapTiles.push_back(m_mapTiles[row][col]);
		}
	}
}
