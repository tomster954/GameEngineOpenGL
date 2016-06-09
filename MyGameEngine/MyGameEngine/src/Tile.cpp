#include "Tile.h"
#include "Texture.h"
#include "Sprite_Batch.h"
#include "glm/glm.hpp"

Tile::Tile()
{
	
}

Tile::Tile(Texture *a_textureMap, int a_tileID, glm::vec2 a_quadSize, glm::vec2 a_portionSize, glm::vec3 a_worldPos)
{
	//setting vars
	m_textureMap	= a_textureMap;
	m_tileID		= a_tileID;
	m_quadSize		= a_quadSize;
	m_portionSize	= a_portionSize;
	m_worldPos		= a_worldPos;

	//todo Calculate the text coord
	m_tileTexture = new Texture(m_textureMap, m_quadSize, m_portionSize, m_worldPos, m_textCoord);
}

Tile::~Tile()
{

}

void Tile::Draw(Sprite_Batch *a_SB)
{
	a_SB->DrawSprite(m_tileTexture);
}

