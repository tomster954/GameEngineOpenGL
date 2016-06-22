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
	Camera();
	~Camera();
	void Initialise(glm::vec3 a_pos, glm::vec3 a_direction, GLFWwindow *a_pWindow);
	void Draw();
	void Update(float a_dt);

	void AddRotation(char a_axis, float degrees);

	void KeyInputHandling();
	void MouseInputHandling();
	void SetPosition(glm::vec3 a_pos){ m_cameraPosition = a_pos; }
	glm::vec3 GetPosition(){ return m_cameraPosition; }

	glm::vec3 m_cameraPosition;
private:
	GLFWwindow *m_pWindow;


	glm::vec3 m_direction;
	glm::vec3 m_up;
	glm::vec3 m_right;

	glm::vec2 m_cursorPos;
	glm::vec2 m_cursorLastPos;
	glm::vec2 m_cursorOffset;

	glm::mat3 m_camRotation;

	float m_dt;

	int m_winWidth, m_winHeight;
	float m_winRatio;
	float m_cameraMoveSpeed;

	float m_rotation;

	bool m_pressed;
};
#endif