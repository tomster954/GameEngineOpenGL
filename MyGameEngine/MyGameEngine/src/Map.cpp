#include "Map.h"

#include <iostream>
#include <fstream>
#include <algorithm>

#include "Sprite_Batch.h"
//#include "Texture.h"

Map::Map(char *a_mapDataFile)
{
	Load(a_mapDataFile);
	
}

Map::~Map()
{
}

void Map::Load(char *a_mapDataFile)
{
	ReadMapData(a_mapDataFile);
	SortMapData();

	m_textureTileMap = new Texture("./resources/Maps/Tiles/map_tiles.png", glm::vec2(0, 0), glm::vec3(0, 0, -40));
}

void Map::Update()
{

}

void Map::Draw(Sprite_Batch *a_SB)
{
	a_SB->DrawSprite(m_textureTileMap);
	//TODO, maybe have a vector of the different textures for tiles and then take the texture from there when drawing tiles,
	//	have a tile class for each tile and add them to a vector/list? also need to load the texture map to get tils from.
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
	m_tileWidth = std::atoi(FindData("tilewidth=\"", '"').c_str());
	m_tileHeight = std::atoi(FindData("tileheight=\"", '"').c_str());

	m_mapWidth = std::atoi(FindData("width=\"", '"').c_str());
	m_mapHeight = std::atoi(FindData("height=\"", '"').c_str());

	m_tileSpacing = std::atoi(FindData("spacing=\"", '"').c_str());
	m_tileMargin = std::atoi(FindData("margin=\"", '"').c_str());
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