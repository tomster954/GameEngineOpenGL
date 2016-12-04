#include "Sprite_Batch.h"
#include "Texture.h"
#include "Application.h"

#include "SOIL2.h"

#include "glm/glm.hpp"

#include <list>

Sprite_Batch::Sprite_Batch(Application *a_pApp)
{
	m_pApp = a_pApp;
}

Sprite_Batch::~Sprite_Batch()
{
}

void Sprite_Batch::Draw()
{
	//for transperant textures (works atm)
	//----------------------------------------------------------------------------
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDepthMask(GL_FALSE);
	//----------------------------------------------------------------------------

	//Draw every sprite passed in this frame
	for (int i = 0; i < m_textures.size(); i++)
	{
		Texture *itr = m_textures[i];
		if (itr == NULL)
			continue;
		//Vars
		float hTW, hTH;				//Half Texture Windth / Height
		glm::vec2 size;				//Texture size
		glm::vec2 TL, TR, BL, BR;	//Top left, top right, bot left, bot right
		glm::vec3 pos;				//Texture Pos
		GLuint ID;					//Texture ID

		//Setting vars
		size	= itr->GetQuadSize();
		hTW		= size.x / 2;
		hTH		= size.y / 2;
		pos		= itr->GetPosition();
		ID		= itr->GetTextureID();

		glm::mat2x4 coords = itr->GetTextureCoords();
		TL = glm::vec2(coords[0].x, coords[0].y);	//Default: (0, 1)
		TR = glm::vec2(coords[0].z, coords[0].w);	//Default: (1, 1);
		BR = glm::vec2(coords[1].x, coords[1].y);	//Default: (1, 0);
		BL = glm::vec2(coords[1].z, coords[1].w);	//Default: (0, 0);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(pos.x, pos.y, pos.z);
		glRotatef(itr->GetRotation(), 0, 0, 1);

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, ID);
		
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	
		//note 0,0 is bottom left
		glBegin(GL_QUADS);
		if (itr->IsDrawingFromCentre())
		{
			glTexCoord2f(TL.x, TL.y);		glVertex2f(-hTW, hTH);
			glTexCoord2f(TR.x, TR.y);		glVertex2f(hTW, hTH);
			glTexCoord2f(BR.x, BR.y);		glVertex2f(hTW, -hTH);
			glTexCoord2f(BL.x, BL.y);		glVertex2f(-hTW, -hTH);
		}
		else
		{
			glTexCoord2f(TL.x, TL.y);		glVertex2f(0, size.y);
			glTexCoord2f(TR.x, TR.y);		glVertex2f(size.x, size.x);
			glTexCoord2f(BR.x, BR.y);		glVertex2f(size.x, 0);
			glTexCoord2f(BL.x, BL.y);		glVertex2f(0, 0);
		}
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