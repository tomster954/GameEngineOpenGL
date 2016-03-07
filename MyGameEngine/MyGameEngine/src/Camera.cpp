#include "Camera.h"

//GLEW
#define GLEW_STATIC
#include "glew.h"

//GLU
#include <GL/glu.h>

//GLFW
#include "glfw3.h"

Camera::Camera(glm::vec3 a_pos, glm::vec3 a_direction, GLFWwindow *a_pWindow)
{
	m_pWindow = a_pWindow;
	m_worldPosition = a_pos;
	m_direction = a_direction;
	
	m_cameraMoveSpeed = 50;

	Initialise();
}

Camera::~Camera()
{
}

void Camera::Initialise()
{
	
}

void Camera::Draw()
{
	glViewport(0, 0, m_winWidth, m_winHeight);

	//Setting perspective
	glfwGetFramebufferSize(m_pWindow, &m_winWidth, &m_winHeight);
	m_winRatio = (float)m_winWidth / (float)m_winWidth;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, m_winRatio, 0.1, 1000);

	//PROJECTION VIEW
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, m_winRatio, 0.1, 1000);

	glm::vec3 facing = m_direction + m_worldPosition;
	gluLookAt(m_worldPosition.x, m_worldPosition.y, m_worldPosition.z, facing.x, facing.y, facing.z, 0, 1, 0);
}

void Camera::Update(float a_dt)
{
	m_dt = a_dt;
	ControlInputHandling();
}

void Camera::ControlInputHandling()
{
	if (glfwGetKey(m_pWindow, GLFW_KEY_W) == GLFW_PRESS)
		m_worldPosition.z -= m_cameraMoveSpeed * 10 * m_dt;

	if (glfwGetKey(m_pWindow, GLFW_KEY_A) == GLFW_PRESS)
		m_worldPosition.x -= m_cameraMoveSpeed * 10 * m_dt;

	if (glfwGetKey(m_pWindow, GLFW_KEY_S) == GLFW_PRESS)
		m_worldPosition.z += m_cameraMoveSpeed * 10 * m_dt;

	if (glfwGetKey(m_pWindow, GLFW_KEY_D) == GLFW_PRESS)
		m_worldPosition.x += m_cameraMoveSpeed * 10 * m_dt;
}