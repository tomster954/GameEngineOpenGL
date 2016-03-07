//-----------------------------------------------------------------------------
//Author: Tom solarino
//Description: this is a camera class for the world
//-----------------------------------------------------------------------------

#ifndef CAMERA
#define CAMERA
//GLM
#include "glm/glm.hpp"

struct GLFWwindow;
class Camera
{
public:
	Camera(glm::vec3 a_pos, glm::vec3 a_direction, GLFWwindow *a_pWindow);
	~Camera();
	void Initialise();
	void Draw();
	void Update(float a_dt);

	void ControlInputHandling();

private:
	GLFWwindow *m_pWindow;

	glm::vec3 m_worldPosition;
	glm::vec3 m_direction;
	glm::vec3 m_lookAtPos;

	float m_dt;

	int m_winWidth, m_winHeight;
	float m_winRatio;
	float m_cameraMoveSpeed;
};
#endif