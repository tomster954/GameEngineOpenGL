#include "Map.h"

#include <iostream>
#include <fstream>
#include <algorithm>

Map::Map(char *a_mapDataFile)
{
	ReadMapData(a_mapDataFile);
	SortMapData();
}

Map::~Map()
{
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
	char *needle = "width";
	std::string width =	FindData(needle);


}

std::string Map::FindData(char word[])
{
	//TODO: find the end of the word width
	int c;
	std::vector<char>::iterator it;
	it = std::search(m_fileData.begin(), m_fileData.end(), word, word + sizeof(word));

	if (it != m_fileData.end())
		c = it - m_fileData.begin();
	else
		std::cout << "needle1 not found\n";

	std::string result("");
	for (int i = c + sizeof(word) + 2; m_fileData[i] != 34; i++)
	{
		result += m_fileData[i];
	}
	return result;
}