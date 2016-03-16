#include "Texture.h"

#include "SOIL2.h"

#include "glm/glm.hpp"

Texture::Texture(char *a_fileName, glm::vec2 a_size, glm::vec3 a_pos)
{
	m_textureID = 0;
	m_size = a_size;
	m_pos = a_pos;

	// load an image file directly as a new OpenGL texture
	m_textureID = SOIL_load_OGL_texture
		(
			a_fileName, 
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_NTSC_SAFE_RGB
		);
}

Texture::~Texture()
{
}