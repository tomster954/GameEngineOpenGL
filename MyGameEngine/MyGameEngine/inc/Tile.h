//-----------------------------------------------------------------------------
//Author: Tom Solarino
//Description: this is a tile class that the map will mostly use for the map tiles
//-----------------------------------------------------------------------------

#ifndef TILE
#define TILE

#include "glm/glm.hpp"

class Texture;
class Sprite_Batch;

class Tile
{
public:
	//default constructor
	Tile();
	//destructors
	~Tile();

	//Params:
	//a_textureMap, The texture or tile map for this tile.
	//a_tileID,		The tiles ID on the tile map.
	//a_quadSize,	The size of the image in the screen.
	//a_portionSize,	The size of the portion off the tile map.
	void Initialise(Texture *a_textureMap, int a_tileID, glm::vec2 a_quadSize, glm::vec2 a_portionSize, glm::vec3 a_worldPos, glm::vec2 a_topLeftPx);


	void Draw(Sprite_Batch *a_SB);

	glm::vec3 m_worldPos;		//where this tile sits in the world
private:
	Texture *m_textureMap;		//Tile Texture of Tile sheet with texture coords
	Texture *m_tileTexture;		//The texture of this tile
	int m_tileID;				//The ID of the specific tile needed to be drawn from the texture map e.g. tile 1

	glm::vec2 m_quadSize;		//The images size on screen in game
	glm::vec2 m_portionSize;	//The portion of image being loadded in. e.g. only 30px,30px of a 100px,100px image
	glm::vec2 m_topLeftPx;		//The top left position of the tile in pixels on the tile sheet

};
#endif