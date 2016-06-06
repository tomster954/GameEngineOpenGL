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
	//In: Textures file name, textures size, textures pos, textures text coord in pixels
	Texture(char *a_fileName, glm::vec2 a_size, glm::vec3 a_pos, glm::vec2 a_textCoord);
	~Texture();

	//vars
	GLuint m_textureID;			//The textures ID
	glm::vec2 m_size;			//The Textures Size
	glm::vec3 m_pos;			//The Textures Pos
	glm::vec2 m_textureCoord;	//The Textures Top left, defaul: (0,1)

	glm::vec2 m_textCoordTL;	//Top Left Texture Coordinates
	glm::vec2 m_textCoordTR;	//Top Right Texture Coordinates
	glm::vec2 m_textCoordBR;	//Bottom Left Texture Coordinates
	glm::vec2 m_textCoordBL;	//Bottom Right Texture Coordinates


private:
	void CalculateTextCoords();
};
#endif