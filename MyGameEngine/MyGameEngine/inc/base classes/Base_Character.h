//-----------------------------------------------------------------------------
//Author: Tom Solarino	
//Description: Any object placed in the world inherits from this class
//-----------------------------------------------------------------------------

#ifndef BASE_CHARACTER
#define BASE_CHARACTER

#include "base classes\Base_Object.h"
#include "Texture.h"

struct GLFWwindow;
class Sprite_Batch;

class Base_Character : public Base_Object
{
public:
	Base_Character(GLFWwindow *a_pWindow, glm::vec3 a_startLocation, float a_speed, float a_health, Texture *a_playerTexture);
	~Base_Character();
	
	void Draw(Sprite_Batch *a_SB);
	void Update(float a_dt);

	void HandleInput();

	//void MoveTo(glm::vec3 a_newPosition);

protected:
	GLFWwindow *m_pWindow;
	glm::vec3 m_direction;
	glm::vec3 m_up;
	glm::vec3 m_right;

	float m_speed = 10;
	float m_health = 100;
	Texture *m_playerTexture;
};
#endif