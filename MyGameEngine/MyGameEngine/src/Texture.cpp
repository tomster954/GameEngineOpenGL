#include "Texture.h"

#include "SOIL2.h"

#include "glm/glm.hpp"

Texture::Texture(char *a_fileName, glm::vec2 a_quadSize, glm::vec2 a_portionSize, glm::vec3 a_pos, glm::vec2 a_topLeftPx)
{
	m_drawFromCentre = false;
	m_textureID = 0;
	m_quadSize = a_quadSize;
	m_portionSize = a_portionSize;
	m_pos = a_pos;
	m_topLeftPx = a_topLeftPx;
	m_rotation = 0;

	//Default Texture Coords
	m_textCoordTL = glm::vec2(0, 1);
	m_textCoordTR = glm::vec2(1, 1);
	m_textCoordBR = glm::vec2(1, 0);
	m_textCoordBL = glm::vec2(0, 0);

	// load an image file directly as a new OpenGL texture
	m_textureID = SOIL_load_OGL_texture
		(
			a_fileName, 
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_NTSC_SAFE_RGB
		);

	//gets the images original size
	GetOriginalImageSize();

	//if the size of the texture is 0 get the actual size of the texture
	if (m_quadSize.x <= 0 || m_quadSize.y <= 0)
	{
		m_quadSize.x = m_originalImageSize.x;
		m_quadSize.y = m_originalImageSize.y;
	}
	//if the portion of the image being loaded has a size of 0 get the full image
	if (m_portionSize.x <= 0 || m_portionSize.y <= 0)
	{
		m_portionSize.x = m_originalImageSize.x;
		m_portionSize.y = m_originalImageSize.y;
	}

	CalculateTextCoords();
}

Texture::Texture(Texture *a_texture, glm::vec2 a_quadSize, glm::vec2 a_portionSize, glm::vec3 a_pos, glm::vec2 a_topLeftPx)
{
	//settting this texture vars
	m_drawFromCentre = false;
	m_textureID		= a_texture->m_textureID;
	m_quadSize		= a_quadSize;
	m_portionSize	= a_portionSize;
	m_pos			= a_pos;
	m_topLeftPx		= a_topLeftPx;
	m_rotation = 0;

	m_originalImageSize.x = a_texture->m_originalImageSize.x;
	m_originalImageSize.y = a_texture->m_originalImageSize.y;

	//if the portion of the image being loaded has a size of 0 get the full image
	if (m_portionSize.x <= 0 || m_portionSize.y <= 0)
	{
		m_portionSize.x = m_originalImageSize.x;
		m_portionSize.y = m_originalImageSize.y;
	}

	CalculateTextCoords();
}

Texture::~Texture()
{
}

void Texture::GetOriginalImageSize()
{
	GLint w, h;
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &w);
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &h);
	m_originalImageSize.x = (float)w;
	m_originalImageSize.y = (float)h;
}

void Texture::CalculateTextCoords()
{
	glm::vec2 texelpos = m_topLeftPx;
	texelpos.x += 0.5f; //because the texel coord is the middle of the pixel

	m_textCoordTL.x = texelpos.x / m_originalImageSize.x;
	m_textCoordTL.y = texelpos.y / m_originalImageSize.y;

	m_textCoordTR.x = (texelpos.x + m_portionSize.x - 1) / m_originalImageSize.x;
	m_textCoordTR.y = texelpos.y / m_originalImageSize.y;

	m_textCoordBR.x = (texelpos.x + m_portionSize.x - 1) / m_originalImageSize.x;
	m_textCoordBR.y = (texelpos.y + m_portionSize.y - 1) / m_originalImageSize.y;

	m_textCoordBL.x = texelpos.x / m_originalImageSize.x;
	m_textCoordBL.y = (texelpos.y + m_portionSize.y - 1) / m_originalImageSize.y;
}