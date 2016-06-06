#include "Texture.h"

#include "SOIL2.h"

#include "glm/glm.hpp"

Texture::Texture(char *a_fileName, glm::vec2 a_size, glm::vec3 a_pos, glm::vec2 a_textCoord)
{
	m_textureID = 0;
	m_size = a_size;
	m_pos = a_pos;

	//m_textureCoord = a_textCoord;

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

	//if the size of the texture is 0 get the actual size of the texture
	if (m_size.x <= 0 || m_size.y <= 0)
	{
		GLint w, h;
		glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &w);
		glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &h);
	
		m_size.x = w;
		m_size.y = h;
	}

	CalculateTextCoords();
}

Texture::~Texture()
{
}

void Texture::CalculateTextCoords()
{
	//Todo: Calcualte text coords and figure out what attributes to pass in for the text coords
}