//-----------------------------------------------------------------------------
//Author:: Tom Solarino
//Description:: This handles all texture needing tp be drawn
//-----------------------------------------------------------------------------

#ifndef SPRITE_BATCH
#define SPRITE_BATCH
#include <list>

#include "Texture.h"

class Sprite_Batch
{
public:
	Sprite_Batch();
	~Sprite_Batch();

	//This is called once at the end of main draw function
	void Draw();

	//Add a texture to a list of textures to be drawn
	void DrawSprite(Texture *a_texture);

private:
	std::list<Texture*> m_textures;
};
#endif