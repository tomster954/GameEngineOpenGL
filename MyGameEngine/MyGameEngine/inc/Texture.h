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
	//In: 
	//a_fileName,	The file location of the image to be loaded
	//a_textureSize,	The size of the image on screen, if 0 the original image size will be loaded
	//a_portionSize,	The size of the section loaded in, if 0 the original image size will load
	//a_pos,		The position of the texture from the middle
	//a_textCoord,	Top left of the portion being loaded
	Texture(char *a_fileName, glm::vec2 a_quadSize, glm::vec2 a_portionSize, glm::vec3 a_pos, glm::vec2 a_textCoord);
	Texture(Texture *a_texture, glm::vec2 a_quadSize, glm::vec2 a_portionSize, glm::vec3 a_pos, glm::vec2 a_textCoord);
	~Texture();

	//vars
	GLuint m_textureID;				//The textures ID
	glm::vec2 m_quadSize;			//The images size on screen in game
	glm::vec2 m_portionSize;		//The size of the portion of image being loadded in. e.g. only 30px,30px of a 100px,100px image
	glm::vec2 m_originalImageSize;	//The original size of the image
	glm::vec3 m_pos;				//The Textures Pos
	glm::vec2 m_textureCoord;		//The Textures Top left, defaul: (0,1)

	glm::vec2 m_textCoordTL;	//Top Left Texture Coordinates
	glm::vec2 m_textCoordTR;	//Top Right Texture Coordinates
	glm::vec2 m_textCoordBR;	//Bottom Left Texture Coordinates
	glm::vec2 m_textCoordBL;	//Bottom Right Texture Coordinates

private:
	void GetOriginalImageSize();
	void CalculateTextCoords();
};
#endif