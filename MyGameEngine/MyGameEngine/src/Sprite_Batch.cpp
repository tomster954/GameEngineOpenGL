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
	for (auto itr = m_textures.begin(); itr != m_textures.end(); ++itr)
	{
		//Vars
		glm::vec2 size;				//Texture size
		glm::vec2 TL, TR, BL, BR;	//Top left, top right, bot left, bot right
		glm::vec3 pos;				//Texture Pos
		GLuint ID;					//Texture ID

		float hTW, hTH;				//Half Texture Windth / Height

		TL = glm::vec2(0, 1);
		TR = glm::vec2(1, 1);
		BR = glm::vec2(1, 0);
		BL = glm::vec2(0, 0);

		ID = (*itr)->m_textureID;

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(pos.x, pos.y, pos.z);
		glEnable(GL_TEXTURE_2D);

		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

		glBindTexture(GL_TEXTURE_2D, ID);

		//if the size of the texture is 0 get the actual size of the texture
		if ((*itr)->m_size.x <= 0 || (*itr)->m_size.y <= 0)
		{
			GLint w, h;
			glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &w);
			glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &h);

			(*itr)->m_size.x = w;
			(*itr)->m_size.y = h;
		}

		//Setting vars
		size = (*itr)->m_size;
		pos = (*itr)->m_pos;

		hTW = size.x / 2;
		hTH = size.y / 2;

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glBegin(GL_QUADS);
		glTexCoord2f(TL.x, TL.y);		glVertex2f(-hTW, -hTH);
		glTexCoord2f(TR.x, TR.y);		glVertex2f(hTW, -hTH);
		glTexCoord2f(BR.x, BR.y);		glVertex2f(hTW, hTH);
		glTexCoord2f(BL.x, BL.y);		glVertex2f(-hTW, hTH);
		glEnd();

		//glDisable(GL_BLEND);
		glDisable(GL_TEXTURE_2D);
	}

	//Clear the list of textures so they can be added again
	m_textures.clear();
}

void Sprite_Batch::DrawSprite(Texture *a_texture)
{
	m_textures.push_back(a_texture);
}