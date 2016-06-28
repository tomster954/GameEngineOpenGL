//-----------------------------------------------------------------------------
//Author:: Tom Solarino
//Description:: This handles all texture needing tp be drawn
//-----------------------------------------------------------------------------

#ifndef SPRITE_BATCH
#define SPRITE_BATCH
#include <vector>

#include "Texture.h"

#include "glm/glm.hpp"
class Application;

class Sprite_Batch
{
public:
	Sprite_Batch(Application *a_pApp);
	~Sprite_Batch();

	//This is called once at the end of main draw function
	void Draw();

	//Add a texture to a list of textures to be drawn
	void DrawSprite(Texture *a_texture);

private:
	Application *m_pApp;
	glm::vec2 m_winSize;
	std::vector<Texture*> m_textures;
};
#endif