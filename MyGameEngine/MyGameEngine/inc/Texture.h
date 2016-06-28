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
	//a_quadSize,	The size of the image on screen, if 0 the original image size will be loaded
	//a_portionSize,	The size of the section loaded in, if 0 the original image size will load
	//a_pos,		The position of the texture from the middle
	//a_topLeftPx,	Top left of the portion being loaded, based on the textures original size
	Texture(char *a_fileName, glm::vec2 a_quadSize, glm::vec2 a_portionSize, glm::vec3 a_pos, glm::vec2 a_topLeftPx);
	Texture(Texture *a_texture, glm::vec2 a_quadSize, glm::vec2 a_portionSize, glm::vec3 a_pos, glm::vec2 a_topLeftPx);
	~Texture();

	//Getters
	GLuint GetTextureID(){ return m_textureID; }			//Returns the texture ID
	glm::vec2 GetQuadSize(){ return m_quadSize; }			//Returns the quad size of the texture
	glm::vec2 GetPortionSize(){ return m_portionSize; }		//Returns the portion of the texture wanted to be drawn
	glm::vec3 GetPosition(){ return m_pos; }				//Returns the texture position
	glm::vec2 GetTopLeftPixel(){ return m_topLeftPx; }		//Returns the top left pixel to draw from
	glm::mat2x4 GetTextureCoords() { return glm::mat2x4(m_textCoordTL.x, m_textCoordTL.y, 
														m_textCoordTR.x, m_textCoordTR.y, 
														m_textCoordBR.x, m_textCoordBR.y,
														m_textCoordBL.x, m_textCoordBL.y );}	//Top left, Top right, Bottom right, Bottom left
	bool IsDrawingFromCentre(){ return m_drawFromCentre; }	//Returns whether the texture is drawing from the centre
	float GetRotation(){ return m_rotation; }				//Returns angle in degress

	//Setters
	void DrawFromCentre(bool a_drawFromCentre){ m_drawFromCentre = a_drawFromCentre; }	//Sets draw from centre to attribute
	void SetPosition(glm::vec3 a_pos){ m_pos = a_pos; };								//Sets the textures position
	void SetRotation(float a_angle){ m_rotation = a_angle; }							//Sets the textures rotation
private:
	void GetOriginalImageSize();	//Returns the original images size
	void CalculateTextCoords();		//Calculates the texture coords based off the top left pixel and portion size

	//vars
	bool m_drawFromCentre;
	GLuint m_textureID;				//The textures ID
	glm::vec2 m_quadSize;			//The images size on screen in game
	glm::vec2 m_portionSize;		//The size of the portion of image being loadded in. e.g. only 30px,30px of a 100px,100px image
	glm::vec2 m_originalImageSize;	//The original size of the image
	glm::vec3 m_pos;				//The Textures Pos
	glm::vec2 m_topLeftPx;			//The Textures Top left point in pixels, defaul: (0,0)
	float m_rotation;			//The rotation of the textue

	glm::vec2 m_textCoordTL;	//Top Left Texture Coordinates
	glm::vec2 m_textCoordTR;	//Top Right Texture Coordinates
	glm::vec2 m_textCoordBR;	//Bottom Left Texture Coordinates
	glm::vec2 m_textCoordBL;	//Bottom Right Texture Coordinates
};
#endif