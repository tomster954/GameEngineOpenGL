#include "Tile.h"
#include "Texture.h"
#include "Sprite_Batch.h"
#include "glm/glm.hpp"

Tile::Tile()
{
	
}

void Tile::Initialise(Texture *a_textureMap, int a_tileID, glm::vec2 a_quadSize, glm::vec2 a_portionSize, glm::vec3 a_worldPos, glm::vec2 a_topLeftPx)
{
	//setting vars
	m_textureMap	= a_textureMap;
	m_tileID		= a_tileID;			//The tiles position on the tile sheet
	m_quadSize		= a_quadSize;		//The size of the texture quad
	m_portionSize	= a_portionSize;	//The original size of the tile, being take from the original image
	m_worldPos		= a_worldPos;		//The world position of this tile
	m_topLeftPx		= a_topLeftPx;		//top left position on the tile map where this tile begins

	//todo Calculate the text coord
	m_tileTexture = new Texture(m_textureMap, m_quadSize, m_portionSize, m_worldPos, m_topLeftPx);
}

Tile::~Tile()
{
	delete m_tileTexture;
}

void Tile::Draw(Sprite_Batch *a_SB)
{
	a_SB->DrawSprite(m_tileTexture);
}

