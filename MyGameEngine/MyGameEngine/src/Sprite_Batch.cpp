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
		glm::vec2 size = (*itr)->m_size;
		glm::vec3 pos = (*itr)->m_pos;
		GLuint textID = (*itr)->m_textureID;

		float hBW = size.x / 2; //Half Box Width
		float hBH = size.y / 2; //Half Box Height
		float hBD = 1; //Half Box Depth

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(pos.x, pos.y, pos.z);
		glEnable(GL_TEXTURE_2D);

		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

		glBindTexture(GL_TEXTURE_2D, textID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f);		glVertex2f(-hBW, -hBW);
		glTexCoord2f(1.0f, 1.0f);		glVertex2f(hBW, -hBW);
		glTexCoord2f(1.0f, 0.0f);		glVertex2f(hBW, hBW);
		glTexCoord2f(0.0f, 0.0f);		glVertex2f(-hBW, hBW);
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