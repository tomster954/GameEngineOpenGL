#include "Map.h"

#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>

#include "Sprite_Batch.h"
#include "Tile.h"

Map::Map(char *a_mapDataFile)
{
	Load(a_mapDataFile);
}

Map::~Map()
{
	delete m_tileSheet.m_texture;
}

void Map::Load(char *a_mapDataFile)
{
	ReadMapData(a_mapDataFile);
	SortMapData();

	LoadTiles();
}

void Map::Update()
{

}

void Map::Draw(Sprite_Batch *a_SB)
{	
	//loops rows
	for (int i = 0; i < m_mapHeight; i++)
	{
		for (int j = 0; j < m_mapWidth; j++)
		{
			//todo only draw tiles on screen
			m_mapTiles[i][j]->Draw(a_SB);
		}
	}
}

void Map::LoadTiles()
{
	//setting up vars
	int tileCount = m_mapWidth * m_mapHeight;
	int row = 0;
	int col = 0;
	int initialVal = 0;

	//resizing the 2d vector of tiles
	m_mapTiles.resize(m_mapHeight, std::vector<Tile*>(m_mapWidth, new Tile()));

	//Filling the 2d vector of tiles
	for (int i = 0; i < m_rawTileData.size(); i++)
	{
		//if we reach a new line
		if (m_rawTileData[i] == '\n')
		{
			row++;
			col = 0;
			continue;
		}

		if (m_rawTileData[i] == ',')
		{
			col++;
			continue;
		}

		//finds how many digits are in the current ID
		int digits = 0;
		int tileID = 1;
		for (int j = i; j < m_rawTileData.size(); j++)
		{
			digits++;
			if (m_rawTileData[j + 1] == ',' || m_rawTileData[j + 1] == '\n')
			{
				//Takes the tiles id from the string and coverts it into an int
				tileID = std::stoi(m_rawTileData.substr(i, digits));
				i = j;
				break;
			}
		}
			
		//setting up the next tiles vars
		glm::vec2 quadSize = glm::vec2(m_tileSheet.tileWidth, m_tileSheet.tileHeight);
		glm::vec2 portionSize = glm::vec2(m_tileSheet.tileWidth, m_tileSheet.tileHeight);
		glm::vec2 topLeftPx = FindTileTopLeft(tileID);

		//Makes the middle of the map the middle of the screen
		float x, y;
		x = m_mapWidth * portionSize.x / 2;
		y = m_mapHeight * portionSize.y / 2;
		glm::vec3 worldPos = glm::vec3(quadSize.x * col - x, -quadSize.y * row + y, 0);

		//creat a new tile and add it to the other tiles
		Tile *tile = new Tile();
		tile->Initialise(m_tileSheet.m_texture, tileID, quadSize, portionSize, worldPos, topLeftPx);
		m_mapTiles[row][col] = tile;
	}
}

void Map::ReadMapData(char *a_mapDataFile)
{	
	std::ifstream ifs(a_mapDataFile);

	if (ifs)
	{
		//get the length of the file
		ifs.seekg(0, std::ios::end);
		std::streampos length = ifs.tellg();
		ifs.seekg(0, std::ios::beg);

		//create a buffer to contain the file contents
		std::vector<char> buffer(length);
		ifs.read(&buffer[0], length);
		m_fileData = buffer;
	}
}

void Map::SortMapData()
{
	m_rawTileData = FindData("<data encoding=\"csv\">\n", '<').c_str();

	m_tileSheet.tileWidth = std::atoi(FindData("tilewidth=\"", '"').c_str());
	m_tileSheet.tileHeight = std::atoi(FindData("tileheight=\"", '"').c_str());

	m_mapWidth = std::atoi(FindData("width=\"", '"').c_str());
	m_mapHeight = std::atoi(FindData("height=\"", '"').c_str());

	m_tileSheet.tileSpacing = std::atoi(FindData("spacing=\"", '"').c_str());
	m_tileSheet.tileMargin = std::atoi(FindData("margin=\"", '"').c_str());

	m_tileSheet.columns = std::atoi(FindData("columns=\"", '"').c_str());
	m_tileSheet.tileCount = std::atoi(FindData("tilecount=\"", '"').c_str());

	//calculating rows in the tile sheet off read data
	m_tileSheet.rows = m_tileSheet.tileCount / m_tileSheet.columns;

	//load the tile map assosiated with this map
	std::string filelocation = "./resources/Maps/";
	filelocation.append(FindData("image source=\"", '\"'));
	m_tileSheet.m_texture = new Texture(_strdup(filelocation.c_str()), glm::vec2(0), glm::vec2(0), glm::vec3(0, 0, -500), glm::vec2(0, 1));
}

std::string Map::FindData(std::string a_word, char a_endChar)
{
	//TODO: find the end of the word width
	int startChar;
	int wordlength = a_word.length();
	std::string result("");

	//Searches for the passed in word
	std::vector<char>::iterator it;
	it = std::search(m_fileData.begin(), m_fileData.end(), a_word.c_str(), a_word.c_str() + wordlength);

	//findes the next 
	if (it != m_fileData.end())
		startChar = it - m_fileData.begin() + wordlength;
	else
		return result;

	//adding each char to result
	for (int i = startChar; m_fileData[i] != a_endChar; i++)
		result += m_fileData[i];

	return result;
}

glm::vec2 Map::FindTileTopLeft(int a_tileID)
{
	glm::vec2 pos = glm::vec2(0);

	//X
	//------------------------------------
	int col = a_tileID;

	//finding the column that this tile sits
	for (col; col > m_tileSheet.columns;)
		col -= m_tileSheet.columns;

	pos.x += m_tileSheet.tileMargin;
	pos.x += ((col - 1) * m_tileSheet.tileWidth) + ((col - 1) * m_tileSheet.tileSpacing);
	//------------------------------------

	//Y
	//------------------------------------
	int row;
	row = (a_tileID - 1) / m_tileSheet.columns;
	
	pos.y += m_tileSheet.tileMargin;
	pos.y += (row * m_tileSheet.tileHeight) + (row * m_tileSheet.tileSpacing);
	

	//------------------------------------

	return pos;
}