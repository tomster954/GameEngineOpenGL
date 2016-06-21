#include "Sprite_Batch.h"
#include "Texture.h"

#include "SOIL2.h"

#include "glm/glm.hpp"

#include <list>

Sprite_Batch::Sprite_Batch()
{
}

Sprite_Batch::~Sprite_Batch()
{
}

void Sprite_Batch::Draw()
{
	//Draw every sprite passed in this frame
	//for (auto itr = m_textures.begin(); itr != m_textures.end(); ++itr)
	for (int i = 0; i < m_textures.size(); i++)
	{
		Texture *itr = m_textures[i];

		//Vars
		float hTW, hTH;				//Half Texture Windth / Height
		glm::vec2 size;				//Texture size
		glm::vec2 TL, TR, BL, BR;	//Top left, top right, bot left, bot right
		glm::vec3 pos;				//Texture Pos
		GLuint ID;					//Texture ID
		
		//Values not between 0 and 1 yet...
		TL = glm::vec2(itr->m_textCoordTL.x, itr->m_textCoordTL.y);	//Default: (0, 1)
		TR = glm::vec2(itr->m_textCoordTR.x, itr->m_textCoordTR.y);	//Default: (1, 1);
		BR = glm::vec2(itr->m_textCoordBR.x, itr->m_textCoordBR.y);	//Default: (1, 0);
		BL = glm::vec2(itr->m_textCoordBL.x, itr->m_textCoordBL.y);	//Default: (0, 0);

		//Setting vars
		size	= itr->m_quadSize;
		hTW		= size.x / 2;
		hTH		= size.y / 2;
		pos		= itr->m_pos;
		ID		= itr->m_textureID;

		

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(pos.x, pos.y, pos.z);
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, ID);
		
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	
		glBegin(GL_QUADS);
		glTexCoord2f(TL.x, TL.y);		glVertex2f(-hTW, -hTH);
		glTexCoord2f(TR.x, TR.y);		glVertex2f(hTW, -hTH);
		glTexCoord2f(BR.x, BR.y);		glVertex2f(hTW, hTH);
		glTexCoord2f(BL.x, BL.y);		glVertex2f(-hTW, hTH);
		glEnd();

		glDisable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);
		glFlush();
	}

	//Clear the list of textures so they can be added again
	m_textures.clear();
}

void Sprite_Batch::DrawSprite(Texture *a_texture)
{
	//TODO: maybe instead of clearing all textures at the end we check the 
	//		incoming texture agains the ones we already have and add it if its not there
	m_textures.push_back(a_texture);
}