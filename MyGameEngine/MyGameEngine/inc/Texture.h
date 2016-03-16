//-----------------------------------------------------------------------------
//Author: Tom Solarino	
//Description: This class contains all the data for one texture
//-----------------------------------------------------------------------------

#ifndef TEXTURE
#define TEXTURE

//GLEW
#define GLEW_STATIC
#include "glew.h"

#include "glm/glm.hpp"

class Texture
{
public:
	Texture(char *a_fileName, glm::vec2 a_size, glm::vec3 a_pos);
	~Texture();

	//vars
	GLuint m_textureID;
	glm::vec2 m_size;
	glm::vec3 m_pos;

private:
};
#endif